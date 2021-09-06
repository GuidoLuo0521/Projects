#include "roledatedialog.h"
#include "roleentrydialog.h"

RoleDateDialog::RoleDateDialog(QMainWindow * parent) :
    TableDateDialog(parent)
{
    CreateSpecialDialog();

    InitLayout();

    InitTableView();
    InitSqlTableModel();

    InitSearchDialog();
    InitAddTableInfoDialog();
}

RoleDateDialog::~RoleDateDialog()
{

}

void RoleDateDialog::CreateSpecialDialog()
{
    TableDateDialog::CreateSpecialDialog();
    m_pAddTableInfoDialog = new RoleEntryDialog(this);
}

void RoleDateDialog::InitSqlTableModel()
{
    m_pSqlTableModel->setTable(g_listCMSDB_Table_Filed_Role[Role_TableName]);

    int i = 0;
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "名称");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "状态");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(Role_RoleID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateDepartment = new ComboboxDelegate(this);
    QStringList listRole = EntryAddDialog::GetRoleList();
    for(int i = 0; i < listRole.size(); ++i)
        pComboxDelegateDepartment->PushItem(listRole[i]);
    m_pTableView->setItemDelegateForColumn(Role_RoleName, pComboxDelegateDepartment);

    ComboboxDelegate * pComboxDelegateState = new ComboboxDelegate(this);
    pComboxDelegateState->PushItem("正常");
    pComboxDelegateState->PushItem("撤销");
    m_pTableView->setItemDelegateForColumn(Role_State, pComboxDelegateState);

    m_pSqlTableModel->select();
}

void RoleDateDialog::InitSearchDialog()
{
    m_pSearchDialog->SetSearchMode(SearchDialog::STT_ROLE);

    m_pSearchDockWidget->setWindowTitle("查询角色");
    m_pSearchDockWidget->setWidget(m_pSearchDialog);
}

void RoleDateDialog::InitAddTableInfoDialog()
{
    connect(m_pAddTableInfoDialog, SIGNAL(signalAddSuccess(bool)), this, SLOT(slotUpdateTable(bool)));

    m_pAddDockWidget->setWindowTitle("增加角色");
    m_pAddDockWidget->setWidget(m_pAddTableInfoDialog);
}

void RoleDateDialog::slotFilter(QStringList listFilter)
{
    QString strQuery;
    if(listFilter[SearchDialog::FILTER_NAME] != "")
        strQuery = QString("(RoleName LIKE '%%1%')").arg(listFilter[SearchDialog::FILTER_NAME]);

    if((listFilter[SearchDialog::FILTER_STATE] != ""))
    {
        if(strQuery != "")
            strQuery += " AND ";
        strQuery += QString("(State = '%1')").arg(listFilter[SearchDialog::FILTER_STATE]);
    }

    m_pSqlTableModel->setFilter(strQuery);
    m_pSqlTableModel->select();
}
