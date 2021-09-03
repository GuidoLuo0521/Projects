#include "tablemanagerdialog.h"



TableManagerDialog::TableManagerDialog(QMainWindow * parent) :
    QMainWindow(parent) ,
    m_pAddTableInfoDialog(nullptr)
{

}

TableManagerDialog::~TableManagerDialog()
{

}

QDockWidget *TableManagerDialog::getSearchDockWidget()
{
    return  m_pSearchDockWidget;
}

QDockWidget *TableManagerDialog::getAddDockWidget()
{
    return m_pAddDockWidget;
}

void TableManagerDialog::CreateSpecialDialog()
{
    m_pAddDockWidget = new QDockWidget("", this);
    m_pAddDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    m_pSearchDockWidget = new QDockWidget("", this);
    m_pSearchDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    m_pSearchDialog = new SearchDialog;
    connect(m_pSearchDialog, &SearchDialog::signalFilterChange, this, &TableManagerDialog::slotFilter);

    m_pSqlTableModel = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);;

    m_pTableView = new QTableView;
    m_pTableView->setSortingEnabled(true);
    m_pTableView->setModel(m_pSqlTableModel);
}

void TableManagerDialog::InitTableView()
{
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void TableManagerDialog::InitLayout()
{
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pSearchDockWidget);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pAddDockWidget);
    this->setCentralWidget(m_pTableView);
}

void TableManagerDialog::InitSearchDialog()
{
    m_pSearchDockWidget->setWidget(m_pSearchDialog);
    //m_pSearchDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
}

void TableManagerDialog::InitAddTableInfoDialog()
{
    m_pAddDockWidget->setWidget(m_pAddTableInfoDialog);
    //pAddDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pAddDockWidget);
}

void TableManagerDialog::slotUpdateTable(bool nToBottom)
{
    m_pSqlTableModel->select();
    if(nToBottom)
        m_pTableView->scrollToBottom();
}

