#include "jobdatedialog.h"
#include "jobentrydialog.h"

JobDateDialog::JobDateDialog(QMainWindow * parent ) :
    TableDateDialog(parent)
{
    CreateSpecialDialog();

    InitLayout();

    InitTableView();
    InitSqlTableModel();

    InitSearchDialog();
    InitAddTableInfoDialog();
}

JobDateDialog::~JobDateDialog()
{

}

void JobDateDialog::CreateSpecialDialog()
{
    TableDateDialog::CreateSpecialDialog();
    m_pAddTableInfoDialog = new JobEntryDialog(this);
}


void JobDateDialog::InitSqlTableModel()
{
    m_pSqlTableModel->setTable(g_listCMSDB_Table_Filed_Job[Job_JobTableName]);

    int i = 0;
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "名称");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "基本工资");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "状态");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(Job_JobID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateJobName = new ComboboxDelegate(this);
    QStringList listDepartments = EntryAddDialog::GetDepartmentList();

    for(int i = 0; i < listDepartments.size(); ++i)
        pComboxDelegateJobName->PushItem(listDepartments[i]);
    m_pTableView->setItemDelegateForColumn(Job_JobName, pComboxDelegateJobName);

    ComboboxDelegate * pComboxDelegateState = new ComboboxDelegate(this);
    pComboxDelegateState->PushItem("正常");
    pComboxDelegateState->PushItem("撤销");
    m_pTableView->setItemDelegateForColumn(Job_State, pComboxDelegateState);

    m_pSqlTableModel->select();
}

void JobDateDialog::InitSearchDialog()
{
    m_pSearchDialog->SetSearchMode(SearchDialog::STT_JOB);

    m_pSearchDockWidget->setWidget( m_pSearchDialog);
    m_pSearchDockWidget->setWindowTitle("搜索职务");
}

void JobDateDialog::InitAddTableInfoDialog()
{
    connect(m_pAddTableInfoDialog, SIGNAL(signalAddSuccess(bool)), this, SLOT(slotUpdateTable(bool)));

    m_pAddDockWidget->setWidget( m_pAddTableInfoDialog);
    m_pAddDockWidget->setWindowTitle("增加职务");
}

void JobDateDialog::slotFilter(QStringList listFilter)
{
    QString strQuery;
    if(listFilter[SearchDialog::FILTER_NAME] != "")
        strQuery = QString("(JobName LIKE '%%1%')").arg(listFilter[SearchDialog::FILTER_NAME]);
    if((listFilter[SearchDialog::FILTER_STATE] != ""))
    {
        if(strQuery != "")
            strQuery += " AND ";
        strQuery += QString("(State = '%1')").arg(listFilter[SearchDialog::FILTER_STATE]);
    }

    m_pSqlTableModel->setFilter(strQuery);
    m_pSqlTableModel->select();
}
