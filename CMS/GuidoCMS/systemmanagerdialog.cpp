#include "systemmanagerdialog.h"
#include "ui_systemmanagerdialog.h"
#include "staffinfo.h"
#include "cmsdatabase.h"
#include "cmsdatebasedef.h"


#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QStandardItemModel>

#include "ControlDelegate.h"

SystemManagerDialog::SystemManagerDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemManagerDialog)
{
    ui->setupUi(this);


    InitLayout();
    BindSlot();

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

void SystemManagerDialog::BindSlot()
{
    connect( m_pStaffManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pRoleManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pJobManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pDepartmentManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
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
}
void SystemManagerDialog::InitSqlTableModelRole()
{
    m_pSqlTableModelRole = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);
}
void SystemManagerDialog::InitSqlTableModelStaff()
{
    m_pSqlTableModelStaff = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);

    m_pSqlTableModelStaff->setTable(CMSDB_Filed_Table_Staff::strTableName);

    int i = 0;
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModelStaff->setHeaderData(i++, Qt::Orientation::Horizontal, "姓名");
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
    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(0, readOnlyDelegate);

    DateDelegate * m_pBirthdayDelegate = new DateDelegate(this);
    m_pTableView->setItemDelegateForColumn(3, m_pBirthdayDelegate);
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);

}
void SystemManagerDialog::InitSqlTableModelDepartment()
{
    m_pSqlTableModelDepartment = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);
}


void SystemManagerDialog::SetTableModelTableStaff()
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        m_pSqlTableModelStaff->select();
        m_pSqlTableModelStaff->removeColumn(2);
    }

    m_pTableView->setModel(m_pSqlTableModelStaff);
}

void SystemManagerDialog::SetTableModelTableDepartment()
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        m_pSqlTableModelDepartment->select();
    }

    m_pTableView->setModel(m_pSqlTableModelDepartment);
}

void SystemManagerDialog::SetTableModelTableJob()
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        m_pSqlTableModelJob->select();
    }

    m_pTableView->setModel(m_pSqlTableModelJob);
}

void SystemManagerDialog::SetTableModelTableRole()
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        m_pSqlTableModelRole->select();
    }

    m_pTableView->setModel(m_pSqlTableModelRole);

}
void SystemManagerDialog::InitLayout()
{
    QWidget * ptoolbar = InitToolBar();
    QWidget * ptableview = InitTableView();
    QWidget * psearchview =InitSearchView();

    QSplitter* pMainSplitter = new QSplitter(Qt::Orientation::Horizontal);
    pMainSplitter->addWidget(ptableview);
    pMainSplitter->addWidget(psearchview);

    this->setCentralWidget(pMainSplitter);
}


QWidget* SystemManagerDialog::InitToolBar()
{
    QToolBar* pToolbarMain =  this->addToolBar("管理");

    m_pStaffManager = pToolbarMain->addAction("用户管理");
    m_pRoleManager = pToolbarMain->addAction("角色管理");
    m_pDepartmentManager = pToolbarMain->addAction("部门管理");
    m_pJobManager = pToolbarMain->addAction("职务管理");

    m_pStaffManager->setCheckable(true);
    m_pRoleManager->setCheckable(true);
    m_pDepartmentManager->setCheckable(true);
    m_pJobManager->setCheckable(true);

    return  pToolbarMain;
}


QWidget* SystemManagerDialog::InitTableView()
{
    m_pTableView = new QTableView;

    return  m_pTableView;
}

QWidget* SystemManagerDialog::InitSearchView()
{
    QWidget * pRightWidget = new QWidget;

    QHBoxLayout * pSearchLayout = new QHBoxLayout;
    QLineEdit * pSearchKey = new QLineEdit;
    pSearchKey->setPlaceholderText("搜索内容");
    QPushButton * pBtnSearch = new QPushButton("搜索");
    pSearchLayout->addWidget(pSearchKey);
    pSearchLayout->addWidget(pBtnSearch);

    QHBoxLayout * pAddLayout = new QHBoxLayout;
    QLineEdit * pAddKey = new QLineEdit;
    pAddKey->setPlaceholderText("增加内容");
    QPushButton * pBtnAdd = new QPushButton("增加");
    pAddLayout->addWidget(pAddKey);
    pAddLayout->addWidget(pBtnAdd);

    QVBoxLayout * pRightMainLayout = new QVBoxLayout;
    pRightMainLayout->addLayout(pSearchLayout, 1);
    pRightMainLayout->addLayout(pAddLayout, 5);
    pRightMainLayout->addStretch();

    pRightWidget->setLayout(pRightMainLayout);

    return  pRightWidget;
}



