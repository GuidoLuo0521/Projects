#include "searchdialog.h"
#include "systemmanagerdialog.h"
#include "ui_systemmanagerdialog.h"
#include "common/staffinfo.h"
#include "database/cmsdatabase.h"
#include "database/cmsdatebasedef.h"

#include "form/addtableinfostaffdialog.h"
#include "form/addtableinfodepartmentdialog.h"


#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QStackedWidget>
#include <QTimer>
#include <QDockWidget>

#include "delegate/controldelegate.h"

SystemManagerDialog::SystemManagerDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemManagerDialog)
{
    ui->setupUi(this);

    InitLayout();

    InitSqlTableModel();
    slotTableChange();
}

SystemManagerDialog::~SystemManagerDialog()
{
    delete ui;
}

void SystemManagerDialog::slotTableChange()
{
    QAction * pAction = (QAction*)sender();

    if(pAction == m_pJobManager)
        SetTableModelTableJob();
    else if(pAction == m_pRoleManager)
        SetTableModelTableRole();
    else if(pAction == m_pDepartmentManager)
        SetTableModelTableDepartment();
    else
        SetTableModelTableStaff();

    ActionChecked(pAction);
}

void SystemManagerDialog::slotUpdateTable()
{
    int nIndex = m_pStackedWidget->currentIndex();
    QSqlTableModel * pSqlTableModel = nullptr;
    QTableView * pTableView = nullptr;

    switch (nIndex) {
    case JobWidget:
        pTableView = m_pTableViewJob;
        pSqlTableModel = m_pSqlTableModelJob;
        break;
    case RoleWidget:
        pTableView = m_pTableViewRole;
        pSqlTableModel = m_pSqlTableModelRole;
        break;
    case DepartmentWidget:
        pTableView = m_pTableViewDepartment;
        pSqlTableModel = m_pSqlTableModelDepartment;
        break;
    default:
        pTableView = m_pTableViewStaff;
        pSqlTableModel = m_pSqlTableModelStaff;
        break;
    }

    pSqlTableModel->select();
    pTableView->scrollToBottom();
}

void SystemManagerDialog::slotUpdateTime()
{
    //[1] 获取时间
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString( "yyyy-MM-dd hh:mm:ss"); //设置显示的格式
    m_pStatuTimeLabel->setText(timestr); //设置label的文本内容为时间
}

void SystemManagerDialog::slotFilter(QStringList listFilter)
{
    QString strQuery = "";
    int nMode = m_pSearchDialog->SearchMode();
    if(nMode == SearchDialog::STT_JOB)
    {
        if(listFilter[SearchDialog::FILTER_NAME] != "")
            strQuery = QString("(JobName LIKE '%%1%')").arg(listFilter[SearchDialog::FILTER_NAME]);

        m_pSqlTableModelJob->setFilter(strQuery);
        m_pSqlTableModelJob->select();
    }
    else if (nMode == SearchDialog::STT_STAFF)
    {
        if(listFilter[SearchDialog::FILTER_NAME] != "")
            strQuery = QString("(StaffName LIKE '%%1%')").arg(listFilter[SearchDialog::FILTER_NAME]);

        if(listFilter[SearchDialog::FILTER_SEX] != "")
        {
            if(strQuery != "") strQuery += " AND ";
            strQuery += QString("(Sex = '%1')").arg(listFilter[SearchDialog::FILTER_SEX]);
        }

        if(listFilter[SearchDialog::FILTER_DEPARTMENT] != "")
        {
            if(strQuery != "") strQuery += " AND ";
            strQuery += QString("(Department = '%1')").arg(listFilter[SearchDialog::FILTER_DEPARTMENT]);
        }

        if(listFilter[SearchDialog::FILTER_JOB] != "")
        {
            if(strQuery != "") strQuery += " AND ";
            strQuery += QString("(JobName = '%1')").arg(listFilter[SearchDialog::FILTER_JOB]);
        }

        if(listFilter[SearchDialog::FILTER_WAGE_L] != "")
        {
            if(strQuery != "") strQuery += " AND ";
            strQuery += QString("(Wage >= '%1')").arg(listFilter[SearchDialog::FILTER_WAGE_L]);
        }

        if(listFilter[SearchDialog::FILTER_WAGE_H] != "")
        {
            if(strQuery != "") strQuery += " AND ";
            strQuery += QString("(Wage <= '%1')").arg(listFilter[SearchDialog::FILTER_WAGE_H]);
        }

        m_pSqlTableModelStaff->setFilter(strQuery);
        m_pSqlTableModelStaff->select();
    }
    else if (nMode == SearchDialog::STT_ROLE)
    {
        if(listFilter[SearchDialog::FILTER_NAME] != "")
            strQuery = QString("(RoleName LIKE '%%1%')").arg(listFilter[SearchDialog::FILTER_NAME]);

        m_pSqlTableModelRole->setFilter(strQuery);
        m_pSqlTableModelRole->select();
    }
    else if (nMode == SearchDialog::STT_DEPARTMENT)
    {
        if(listFilter[SearchDialog::FILTER_NAME] != "")
            strQuery = QString("(DepartmentName LIKE '%%1%')").arg(listFilter[SearchDialog::FILTER_NAME]);

        m_pSqlTableModelDepartment->setFilter(strQuery);
        m_pSqlTableModelDepartment->select();
    }
}

void SystemManagerDialog::slotExitLogin()
{
    emit signalExitCurrentAccount(); close();
}

void SystemManagerDialog::slotShowWindow()
{
    CStaffInfo * pStaffInfo = StaffInfoSingleton::GetInstance();
    QString str = QString("当前登录人员：%1 %2 %3")
                      .arg(pStaffInfo->GetDepartment())
                      .arg(pStaffInfo->GetStaffID())
                      .arg(pStaffInfo->GetStaffName());

    m_pStatuAccountLabel->setText(str);
    this->show();
}

void SystemManagerDialog::ActionChecked(QAction * pAction)
{
    m_pStaffManager->setChecked(false);
    m_pRoleManager->setChecked(false);
    m_pDepartmentManager->setChecked(false);
    m_pJobManager->setChecked(false);

    if(pAction == nullptr)
        pAction = m_pStaffManager;

    pAction->setChecked(true);
}

void SystemManagerDialog::InitSqlTableModel()
{
    InitSqlTableModelJob();
    InitSqlTableModelRole();
    InitSqlTableModelStaff();
    InitSqlTableModelDepartment();
}

void SystemManagerDialog::InitSqlTableModelJob()
{
    m_pSqlTableModelJob = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);
    m_pSqlTableModelJob->setTable(g_listCMSDB_Table_Filed_Job[Job_JobTableName]);

    int i = 0;
    m_pSqlTableModelJob->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModelJob->setHeaderData(i++, Qt::Orientation::Horizontal, "名称");
    m_pSqlTableModelJob->setHeaderData(i++, Qt::Orientation::Horizontal, "基本工资");
    m_pSqlTableModelJob->setHeaderData(i++, Qt::Orientation::Horizontal, "状态");
    m_pSqlTableModelJob->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModelJob->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableViewJob->setItemDelegateForColumn(Job_JobID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateJobName = new ComboboxDelegate(this);
    QStringList listDepartments = AddTableInfoDialog::GetDepartmentList();

    for(int i = 0; i < listDepartments.size(); ++i)
        pComboxDelegateJobName->PushItem(listDepartments[i]);
    m_pTableViewJob->setItemDelegateForColumn(Job_JobName, pComboxDelegateJobName);

    ComboboxDelegate * pComboxDelegateState = new ComboboxDelegate(this);
    pComboxDelegateState->PushItem("正常");
    pComboxDelegateState->PushItem("撤销");
    m_pTableViewJob->setItemDelegateForColumn(Job_State, pComboxDelegateState);

    m_pSqlTableModelJob->select();
    m_pTableViewJob->setModel(m_pSqlTableModelJob);
}
void SystemManagerDialog::InitSqlTableModelRole()
{
    m_pSqlTableModelRole = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);
    m_pSqlTableModelRole->setTable(g_listCMSDB_Table_Filed_Role[Role_TableName]);

    int i = 0;
    m_pSqlTableModelRole->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModelRole->setHeaderData(i++, Qt::Orientation::Horizontal, "名称");
    m_pSqlTableModelRole->setHeaderData(i++, Qt::Orientation::Horizontal, "状态");
    m_pSqlTableModelRole->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModelRole->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableViewRole->setItemDelegateForColumn(Role_RoleID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateJobName = new ComboboxDelegate(this);
    QStringList listJobs = AddTableInfoDialog::GetDepartmentList();
    for(int i = 0; i < listJobs.size(); ++i)
        pComboxDelegateJobName->PushItem(listJobs[i]);
    m_pTableViewRole->setItemDelegateForColumn(Role_RoleName, pComboxDelegateJobName);

    ComboboxDelegate * pComboxDelegateState = new ComboboxDelegate(this);
    pComboxDelegateState->PushItem("正常");
    pComboxDelegateState->PushItem("撤销");
    m_pTableViewRole->setItemDelegateForColumn(Role_State, pComboxDelegateState);

    m_pSqlTableModelRole->select();
    m_pTableViewRole->setModel(m_pSqlTableModelRole);
}
void SystemManagerDialog::InitSqlTableModelStaff()
{
    m_pSqlTableModelStaff = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);
    m_pSqlTableModelStaff->setTable(g_listCMSDB_Table_Filed_Staff[Staff_StaffTableName]);

    int i = 0;
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "姓名");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "密码");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "性别");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "生日");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "部门");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "职务");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "工资");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "工龄");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "籍贯");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "学历");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "专业");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "住址");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "邮件");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "电话");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "入职时间");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "离职时间");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    // 设置0列只读
    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableViewStaff->setItemDelegateForColumn(Staff_StaffID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateSex = new ComboboxDelegate(this);
    pComboxDelegateSex->PushItem("男性");
    pComboxDelegateSex->PushItem("女性");
    pComboxDelegateSex->PushItem("未知");
    m_pTableViewStaff->setItemDelegateForColumn(Staff_Sex, pComboxDelegateSex);

    DateDelegate * pBirthdayDelegate = new DateDelegate(this);
    m_pTableViewStaff->setItemDelegateForColumn(Staff_Birthday, pBirthdayDelegate);

    ComboboxDelegate * pComboxDelegateDepartment = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
        pComboxDelegateDepartment->PushItem(g_strListDepartment[i]);
    m_pTableViewStaff->setItemDelegateForColumn(Staff_Department, pComboxDelegateDepartment);

    ComboboxDelegate * pComboxDelegatePlace = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListPlace.size(); ++i)
        pComboxDelegatePlace->PushItem(g_strListPlace[i]);
    m_pTableViewStaff->setItemDelegateForColumn(Staff_Place, pComboxDelegatePlace);

    ComboboxDelegate * pComboxDelegateEducation = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListEducation.size(); ++i)
        pComboxDelegateEducation->PushItem(g_strListEducation[i]);
    m_pTableViewStaff->setItemDelegateForColumn(Staff_Education, pComboxDelegateEducation);

    ComboboxDelegate * pComboxDelegateSpecialty = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListSpecialty.size(); ++i)
        pComboxDelegateSpecialty->PushItem(g_strListSpecialty[i]);
    m_pTableViewStaff->setItemDelegateForColumn(Staff_Specialty, pComboxDelegateSpecialty);

    ComboboxDelegate * pComboxDelegateJobName = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
    {
        QString str = g_strListDepartment[i];
        str.remove("部");
        pComboxDelegateJobName->PushItem(str);
    }
    m_pTableViewStaff->setItemDelegateForColumn(Staff_JobName, pComboxDelegateJobName);

    DateDelegate * pDelegateEnter = new DateDelegate(this);
    m_pTableViewStaff->setItemDelegateForColumn(Staff_EnterCompany, pDelegateEnter);

    DateDelegate * pDelegateLeave = new DateDelegate(this);
    m_pTableViewStaff->setItemDelegateForColumn(Staff_LeaveCompany, pDelegateLeave);

    m_pSqlTableModelStaff->select();
    m_pTableViewStaff->setModel(m_pSqlTableModelStaff);

}

void SystemManagerDialog::InitSqlTableModelDepartment()
{
    m_pSqlTableModelDepartment = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);
    m_pSqlTableModelDepartment->setTable(g_listCMSDB_Table_Filed_Department[Department_DepartmentTableName]);

    int i = 0;
    m_pSqlTableModelDepartment->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModelDepartment->setHeaderData(i++, Qt::Orientation::Horizontal, "名称");
    m_pSqlTableModelDepartment->setHeaderData(i++, Qt::Orientation::Horizontal, "状态");
    m_pSqlTableModelDepartment->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModelDepartment->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableViewDepartment->setItemDelegateForColumn(Department_DepartmentID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateDepartment = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
        pComboxDelegateDepartment->PushItem(g_strListDepartment[i]);
    m_pTableViewDepartment->setItemDelegateForColumn(Department_DepartmentName, pComboxDelegateDepartment);

    ComboboxDelegate * pComboxDelegateState = new ComboboxDelegate(this);
    pComboxDelegateState->PushItem("正常");
    pComboxDelegateState->PushItem("撤销");
    m_pTableViewDepartment->setItemDelegateForColumn(Department_State, pComboxDelegateState);

    m_pSqlTableModelDepartment->select();
    m_pTableViewDepartment->setModel(m_pSqlTableModelDepartment);
}

QSqlTableModel *SystemManagerDialog::GetCurrentSqlTableModel()
{
    int nIndex = m_pStackedWidget->currentIndex();
    if(nIndex == DepartmentWidget)
        return m_pSqlTableModelDepartment;
    else if(nIndex == JobWidget)
        return m_pSqlTableModelJob;
    else if(nIndex == RoleWidget)
        return m_pSqlTableModelRole;

    return  m_pSqlTableModelStaff;
}

void SystemManagerDialog::SetTableModelTableStaff()
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        pDB->LDB_Log_INFO("select Staff");
        m_pSqlTableModelStaff->select();
    }

    m_pSearchDialog->SetSearchMode(SearchDialog::STT_STAFF);
    m_pStackedWidget->setCurrentIndex(StaffWidget);
}

void SystemManagerDialog::SetTableModelTableRole()
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        pDB->LDB_Log_INFO("select Role");
        m_pSqlTableModelRole->select();
    }

    m_pSearchDialog->SetSearchMode(SearchDialog::STT_ROLE);
    m_pStackedWidget->setCurrentIndex(RoleWidget);

}

void SystemManagerDialog::SetTableModelTableDepartment()
{    
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        pDB->LDB_Log_INFO("select Department");
        m_pSqlTableModelDepartment->select();
    }

    m_pSearchDialog->SetSearchMode(SearchDialog::STT_DEPARTMENT);
    m_pStackedWidget->setCurrentIndex(DepartmentWidget);
}

void SystemManagerDialog::SetTableModelTableJob()
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        pDB->LDB_Log_INFO("select Job");
        m_pSqlTableModelJob->select();
        pDB->LDB_Log_ERROR(m_pSqlTableModelJob->lastError().text());
    }

    m_pSearchDialog->SetSearchMode(SearchDialog::STT_JOB);
    m_pStackedWidget->setCurrentIndex(JobWidget);    
}

void SystemManagerDialog::InitLayout()
{
    setWindowTitle("系统管理");

    QWidget * ptoolbar = InitToolBar();
    QWidget * pstatubar = InitStatuBar();
    QWidget * ptableviewStaff = InitTableViewStaff();
    QWidget * ptableviewDepartment = InitTableViewDepartment();
    QWidget * ptableviewRole = InitTableViewRole();
    QWidget * ptableviewJob = InitTableViewJob();
    //QWidget * psearchview =InitSearchView();

    //////////////////////////////////////////////////////
    // 查询
    m_pSearchDockWidget = new QDockWidget("查询信息", this);
    m_pSearchDialog = new SearchDialog;

    connect(m_pSearchDialog, &SearchDialog::signalFilterChange, this, &SystemManagerDialog::slotFilter);

    m_pSearchDockWidget->setWidget(m_pSearchDialog);
    m_pSearchDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pSearchDockWidget);

    QDockWidget *pSearchDockWidget = new QDockWidget("添加人员", this);
    AddTableInfoStaffDialog * pStaffInfoDialog = new AddTableInfoStaffDialog;
    pSearchDockWidget->setWidget(pStaffInfoDialog);
    pSearchDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, pSearchDockWidget);
    connect(pStaffInfoDialog, &AddTableInfoStaffDialog::signalAddSuccess, this, &SystemManagerDialog::slotUpdateTable);

    m_pStackedWidget = new QStackedWidget;
    m_pStackedWidget->addWidget(ptableviewStaff);
    m_pStackedWidget->addWidget(ptableviewDepartment);
    m_pStackedWidget->addWidget(ptableviewJob);
    m_pStackedWidget->addWidget(ptableviewRole);

    //QSplitter* pMainSplitter = new QSplitter(Qt::Orientation::Horizontal);
    //pMainSplitter->addWidget(ptableview);
    //pMainSplitter->addWidget(psearchview);

    m_pTableViewStaff->setSortingEnabled(true);
    m_pTableViewDepartment->setSortingEnabled(true);
    m_pTableViewRole->setSortingEnabled(true);
    m_pTableViewJob->setSortingEnabled(true);

    this->setCentralWidget(m_pStackedWidget);
}

QWidget* SystemManagerDialog::InitToolBar()
{
    QToolBar* pToolbarMain =  this->addToolBar("管理");
    pToolbarMain->setMovable(false);
    pToolbarMain->setFloatable(false);

    m_pStaffManager =       pToolbarMain->addAction("用户");
    m_pDepartmentManager =  pToolbarMain->addAction("部门");
    m_pJobManager =         pToolbarMain->addAction("职务");
    m_pRoleManager =        pToolbarMain->addAction("角色");

    //2011-11-23-QTooBar中最右一个图标的靠右对齐方式
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //toolBar is a pointer to an existing toolbar
    pToolbarMain->addWidget(spacer);
    pToolbarMain->setFloatable(false);
    m_pExit =  pToolbarMain->addAction("退出登录");

    m_pJobManager->setCheckable(true);
    m_pRoleManager->setCheckable(true);
    m_pStaffManager->setCheckable(true);    
    m_pDepartmentManager->setCheckable(true);

    connect( m_pJobManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pRoleManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pStaffManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pDepartmentManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);

    connect( m_pExit, &QAction::triggered, this, &SystemManagerDialog::slotExitLogin);

    return  pToolbarMain;
}

QWidget *SystemManagerDialog::InitStatuBar()
{
    QStatusBar * pStatubar = this->statusBar();
    m_pStatuTimeLabel = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    pStatubar->addPermanentWidget(m_pStatuTimeLabel);

    QTimer * pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, &QTimer::timeout, this, &SystemManagerDialog::slotUpdateTime);
    pTimer->start();

    m_pStatuAccountLabel = new QLabel("当前登录人员：");
    pStatubar->addWidget(m_pStatuAccountLabel);

    return pStatubar;

}
QWidget* SystemManagerDialog::InitTableViewStaff()
{
    m_pTableViewStaff = new QTableView;
    m_pTableViewStaff->setSelectionMode(QAbstractItemView::SingleSelection);

    return  m_pTableViewStaff;
}
QWidget* SystemManagerDialog::InitTableViewDepartment()
{
    m_pTableViewDepartment = new QTableView;
    m_pTableViewDepartment->setSelectionMode(QAbstractItemView::SingleSelection);

    return  m_pTableViewDepartment;
}
QWidget* SystemManagerDialog::InitTableViewRole()
{
    m_pTableViewRole = new QTableView;
    m_pTableViewRole->setSelectionMode(QAbstractItemView::SingleSelection);

    return  m_pTableViewRole;
}
QWidget* SystemManagerDialog::InitTableViewJob()
{
    m_pTableViewJob = new QTableView;
    m_pTableViewJob->setSelectionMode(QAbstractItemView::SingleSelection);

    return  m_pTableViewJob;
}


