#include "departmentdatedialog.h"
#include "departmententrydialog.h"

#include <QDockWidget>

DepartmentDateDialog::DepartmentDateDialog(QMainWindow * parent ) :
    TableDateDialog(parent)
{
    CreateSpecialDialog();

    InitLayout();

    InitTableView();
    InitSqlTableModel();

    InitSearchDialog();
    InitAddTableInfoDialog();
}

DepartmentDateDialog::~DepartmentDateDialog()
{

}

void DepartmentDateDialog::CreateSpecialDialog()
{
    TableDateDialog::CreateSpecialDialog();
    m_pAddTableInfoDialog = new DepartmentEntryDialog(this);
}


void DepartmentDateDialog::InitSqlTableModel()
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

void DepartmentDateDialog::InitSearchDialog()
{
    m_pSearchDialog->SetSearchMode(SearchDialog::STT_DEPARTMENT);

    m_pSearchDockWidget->setWidget( m_pSearchDialog);
    m_pSearchDockWidget->setWindowTitle("搜索部门");
}

void DepartmentDateDialog::InitAddTableInfoDialog()
{
    connect(m_pAddTableInfoDialog, SIGNAL(signalAddSuccess(bool)), this, SLOT(slotUpdateTable(bool)));

    m_pAddDockWidget->setWidget( m_pAddTableInfoDialog);
    m_pAddDockWidget->setWindowTitle("增加部门");
}

void DepartmentDateDialog::slotFilter(QStringList listFilter)
{
    QString strQuery;
    if(listFilter[SearchDialog::FILTER_NAME] != "")
        strQuery = QString("(DepartmentName LIKE '%%1%')").arg(listFilter[SearchDialog::FILTER_NAME]);

    if((listFilter[SearchDialog::FILTER_STATE] != ""))
    {
        if(strQuery != "")
            strQuery += " AND ";
        strQuery += QString("(State = '%1')").arg(listFilter[SearchDialog::FILTER_STATE]);
    }

    m_pSqlTableModel->setFilter(strQuery);
    m_pSqlTableModel->select();
}
