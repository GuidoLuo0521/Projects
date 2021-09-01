#include "tablestaffmanagerdialog.h"
#include "delegate/controldelegate.h"
#include "form/addtableinfostaffdialog.h"

#include <QDockWidget>

TableStaffManagerDialog::TableStaffManagerDialog(QMainWindow * parent ) :
    TableManagerDialog(parent)
{
    CreateAddInforDialog();

    InitLayout();

    InitTableView();
    InitSqlTableModel();

    InitSearchDialog();
    InitAddTableInfoDialog();
}

void TableStaffManagerDialog::CreateAddInforDialog()
{
    m_pAddTableInfoDialog = new AddTableInfoStaffDialog(this);
    connect(m_pAddTableInfoDialog, SIGNAL(signalAddSuccess(bool)), this, SLOT(slotUpdateTable(bool)));

    //connect(m_pAddTableInfoDialog, &AddTableInfoDialog::signalAddSuccess, this, &TableManagerDialog::slotUpdateTable);
    //connect(m_pAddTableInfoDialog, &AddTableInfoStaffDialog::signalAddSuccess, this, &TableManagerDialog::slotUpdateTable);
}

void TableStaffManagerDialog::InitLayout()
{
    // 左边为列表，右边上面为查询，下面为增加

#if 0
    QSplitter * pMainSpltter = new QSplitter(Qt::Orientation::Horizontal, this);
    QSplitter * pRightSpltter = new QSplitter(Qt::Orientation::Vertical, pMainSpltter);

    pRightSpltter->addWidget(m_pSearchDialog);
    pRightSpltter->addWidget(m_pAddTableInfoDialog);

    pMainSpltter->addWidget(m_pTableView);
    pMainSpltter->addWidget(pRightSpltter);

    pMainLayout->addWidget(pMainSpltter);

#else
    this->setCentralWidget(m_pTableView);

    QDockWidget * m_pSearchDockWidget = new QDockWidget("查询信息", this);
    m_pSearchDockWidget->setWidget(m_pSearchDialog);
    m_pSearchDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pSearchDockWidget);

    QDockWidget *pAddDockWidget = new QDockWidget("添加人员", this);
    pAddDockWidget->setWidget(m_pAddTableInfoDialog);
    pAddDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, pAddDockWidget);
#endif

}

void TableStaffManagerDialog::InitTableView()
{
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void TableStaffManagerDialog::InitSqlTableModel()
{
    m_pSqlTableModel->setTable(g_listCMSDB_Table_Filed_Staff[Staff_StaffTableName]);

    int i = 0;
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "姓名");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "密码");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "性别");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "生日");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "部门");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "职务");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "工资");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "工龄");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "籍贯");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "学历");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "专业");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "住址");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "邮件");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "电话");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "入职时间");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "离职时间");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    // 设置0列只读
    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(Staff_StaffID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateSex = new ComboboxDelegate(this);
    pComboxDelegateSex->PushItem("男性");
    pComboxDelegateSex->PushItem("女性");
    pComboxDelegateSex->PushItem("未知");
    m_pTableView->setItemDelegateForColumn(Staff_Sex, pComboxDelegateSex);

    DateDelegate * pBirthdayDelegate = new DateDelegate(this);
    m_pTableView->setItemDelegateForColumn(Staff_Birthday, pBirthdayDelegate);

    ComboboxDelegate * pComboxDelegateDepartment = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
        pComboxDelegateDepartment->PushItem(g_strListDepartment[i]);
    m_pTableView->setItemDelegateForColumn(Staff_Department, pComboxDelegateDepartment);

    ComboboxDelegate * pComboxDelegatePlace = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListPlace.size(); ++i)
        pComboxDelegatePlace->PushItem(g_strListPlace[i]);
    m_pTableView->setItemDelegateForColumn(Staff_Place, pComboxDelegatePlace);

    ComboboxDelegate * pComboxDelegateEducation = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListEducation.size(); ++i)
        pComboxDelegateEducation->PushItem(g_strListEducation[i]);
    m_pTableView->setItemDelegateForColumn(Staff_Education, pComboxDelegateEducation);

    ComboboxDelegate * pComboxDelegateSpecialty = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListSpecialty.size(); ++i)
        pComboxDelegateSpecialty->PushItem(g_strListSpecialty[i]);
    m_pTableView->setItemDelegateForColumn(Staff_Specialty, pComboxDelegateSpecialty);

    ComboboxDelegate * pComboxDelegateJobName = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
    {
        QString str = g_strListDepartment[i];
        str.remove("部");
        pComboxDelegateJobName->PushItem(str);
    }
    m_pTableView->setItemDelegateForColumn(Staff_JobName, pComboxDelegateJobName);

    DateDelegate * pDelegateEnter = new DateDelegate(this);
    m_pTableView->setItemDelegateForColumn(Staff_EnterCompany, pDelegateEnter);

    DateDelegate * pDelegateLeave = new DateDelegate(this);
    m_pTableView->setItemDelegateForColumn(Staff_LeaveCompany, pDelegateLeave);

    m_pSqlTableModel->select();
}

void TableStaffManagerDialog::InitSearchDialog()
{
    m_pSearchDialog->SetSearchMode(SearchDialog::STT_STAFF);
}

void TableStaffManagerDialog::InitAddTableInfoDialog()
{

}

void TableStaffManagerDialog::slotFilter(QStringList listFilter)
{
    QString strQuery;
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

    m_pSqlTableModel->setFilter(strQuery);
    m_pSqlTableModel->select();
}
