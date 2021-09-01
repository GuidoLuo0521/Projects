#include "tablemanagerdialog.h"



TableManagerDialog::TableManagerDialog(QMainWindow * parent) :
    QMainWindow(parent) ,
    m_pAddTableInfoDialog(nullptr)
{

    m_pAddDockWidget = new QDockWidget("", this);
    m_pSearchDockWidget = new QDockWidget("", this);

    m_pSearchDialog = new SearchDialog;
    connect(m_pSearchDialog, &SearchDialog::signalFilterChange, this, &TableManagerDialog::slotFilter);

    m_pSqlTableModel = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);;

    m_pTableView = new QTableView;
    m_pTableView->setSortingEnabled(true);
    m_pTableView->setModel(m_pSqlTableModel);
}

TableManagerDialog::~TableManagerDialog()
{

}

void TableManagerDialog::InitTableView()
{
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void TableManagerDialog::slotUpdateTable(bool nToBottom)
{
    m_pSqlTableModel->select();
    if(nToBottom)
        m_pTableView->scrollToBottom();
}

