#include "tabledatedialog.h"



TableDateDialog::TableDateDialog(QMainWindow * parent) :
    QMainWindow(parent) ,
    m_pAddTableInfoDialog(nullptr)
{

}

TableDateDialog::~TableDateDialog()
{

}

QDockWidget *TableDateDialog::getSearchDockWidget()
{
    return  m_pSearchDockWidget;
}

QDockWidget *TableDateDialog::getAddDockWidget()
{
    return m_pAddDockWidget;
}

void TableDateDialog::CreateSpecialDialog()
{
    m_pAddDockWidget = new QDockWidget("", this);
    m_pAddDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    m_pSearchDockWidget = new QDockWidget("", this);
    m_pSearchDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);

    m_pSearchDialog = new SearchDialog;
    connect(m_pSearchDialog, &SearchDialog::signalFilterChange, this, &TableDateDialog::slotFilter);

    m_pSqlTableModel = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);;

    m_pTableView = new QTableView;
    m_pTableView->setSortingEnabled(true);
    m_pTableView->setModel(m_pSqlTableModel);
}

void TableDateDialog::InitTableView()
{
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void TableDateDialog::InitLayout()
{
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pSearchDockWidget);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pAddDockWidget);
    this->setCentralWidget(m_pTableView);
}

void TableDateDialog::InitSearchDialog()
{
    m_pSearchDockWidget->setWidget(m_pSearchDialog);
    //m_pSearchDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
}

void TableDateDialog::InitAddTableInfoDialog()
{
    m_pAddDockWidget->setWidget(m_pAddTableInfoDialog);
    //pAddDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, m_pAddDockWidget);
}

void TableDateDialog::slotUpdateTable(bool nToBottom)
{
    m_pSqlTableModel->select();
    if(nToBottom)
        m_pTableView->scrollToBottom();
}

