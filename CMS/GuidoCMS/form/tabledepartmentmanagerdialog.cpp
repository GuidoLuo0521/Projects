#include "tabledepartmentmanagerdialog.h"
#include "addtableinfodepartmentdialog.h"

#include <QDockWidget>

TableDepartmentManagerDialog::TableDepartmentManagerDialog(QMainWindow * parent ) :
    TableManagerDialog(parent)
{
    CreateSpecialDialog();

    InitLayout();

    InitTableView();
    InitSqlTableModel();

    InitSearchDialog();
    InitAddTableInfoDialog();
}

TableDepartmentManagerDialog::~TableDepartmentManagerDialog()
{

}

void TableDepartmentManagerDialog::CreateSpecialDialog()
{
    m_pAddTableInfoDialog = new AddTableInfoDepartmentDialog(this);
}

void TableDepartmentManagerDialog::InitLayout()
{
    m_pSearchDockWidget->setWindowTitle("查询部门");
    m_pSearchDockWidget->setWidget(m_pSearchDialog);
    //m_pSearchDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pSearchDockWidget);

    m_pAddDockWidget->setWindowTitle("增加部门");
    m_pAddDockWidget->setWidget(m_pAddTableInfoDialog);
    //pAddDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pAddDockWidget);

    this->setCentralWidget(m_pTableView);
}


void TableDepartmentManagerDialog::InitSqlTableModel()
{
    m_pSqlTableModel->setTable(g_listCMSDB_Table_Filed_Department[Department_DepartmentTableName]);

    int i = 0;
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "名称");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "状态");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(Department_DepartmentID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateDepartment = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
        pComboxDelegateDepartment->PushItem(g_strListDepartment[i]);
    m_pTableView->setItemDelegateForColumn(Department_DepartmentName, pComboxDelegateDepartment);

    ComboboxDelegate * pComboxDelegateState = new ComboboxDelegate(this);
    pComboxDelegateState->PushItem("正常");
    pComboxDelegateState->PushItem("撤销");
    m_pTableView->setItemDelegateForColumn(Department_State, pComboxDelegateState);

    m_pSqlTableModel->select();
}

void TableDepartmentManagerDialog::InitSearchDialog()
{
    m_pSearchDialog->SetSearchMode(SearchDialog::STT_DEPARTMENT);
}

void TableDepartmentManagerDialog::InitAddTableInfoDialog()
{
    connect(m_pAddTableInfoDialog, SIGNAL(signalAddSuccess(bool)), this, SLOT(slotUpdateTable(bool)));
}

void TableDepartmentManagerDialog::slotFilter(QStringList listFilter)
{
    QString strQuery;
    if(listFilter[SearchDialog::FILTER_NAME] != "")
        strQuery = QString("(DepartmentName LIKE '%%1%')").arg(listFilter[SearchDialog::FILTER_NAME]);

    m_pSqlTableModel->setFilter(strQuery);
    m_pSqlTableModel->select();
}
