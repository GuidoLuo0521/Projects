#include "weeklyreportcommitdialog.h"
#include "weeklyreportdialog.h"
#include "weeklyreporthistorydialog.h"

#include <QSqlTableModel>
#include <QStandardItemModel>

WeeklyReportDialog::WeeklyReportDialog(QWidget *parent) :
    CMSBaseWidget(parent)
{
    InitLayout();
}

WeeklyReportDialog::~WeeklyReportDialog()
{

}

void WeeklyReportDialog::slotShowDialog(WeeklyReportDialog::WeeklyReportDialogType type)
{
    ChangeActionChecked(type);
    m_pMainStackWidget->setCurrentIndex(type);
}

void WeeklyReportDialog::slotToolbarActionClicked()
{
    QAction * pAction = (QAction * )sender();
    if(pAction == m_pActionCommitReport)
    {
        emit signalShowCurrentDialog(CommitDialog);
    }
    else if (pAction == m_pActionHistoryReport)
    {
        emit signalShowCurrentDialog(HistoryDialog);
    }
}

void WeeklyReportDialog::InitLayout()
{
    QWidget* pToolBar = InitToolBar();

    QVBoxLayout * pMainLayout = new QVBoxLayout;
    m_pMainStackWidget = new QStackedWidget;

    ///////// history dialog
    WeeklyReportHistoryDialog * pHistoryWidget = new WeeklyReportHistoryDialog;
    m_pMainStackWidget->addWidget(pHistoryWidget);

    /////////
    WeeklyReportCommitDialog * pCommitWidget = new WeeklyReportCommitDialog;
    m_pMainStackWidget->addWidget(pCommitWidget);

    pMainLayout->addWidget(pToolBar);
    pMainLayout->addWidget(m_pMainStackWidget);

    connect(this, &WeeklyReportDialog::signalShowCurrentDialog, this, &WeeklyReportDialog::slotShowDialog);

    this->setLayout(pMainLayout);
}

QWidget* WeeklyReportDialog::InitToolBar()
{
    //QToolBar* pToolbarMain =  this->addToolBar("管理");
    QToolBar* pToolbarMain =  new QToolBar("管理");

    pToolbarMain->setMovable(false);
    pToolbarMain->setFloatable(false);

    m_pActionHistoryReport = pToolbarMain->addAction("历史周报");
    m_pActionCommitReport =  pToolbarMain->addAction("提交周报");

    m_pActionCommitReport->setCheckable(true);
    m_pActionHistoryReport->setCheckable(true);

    connect( m_pActionCommitReport, &QAction::triggered, this, &WeeklyReportDialog::slotToolbarActionClicked);
    connect( m_pActionHistoryReport, &QAction::triggered, this, &WeeklyReportDialog::slotToolbarActionClicked);

    m_pActionHistoryReport->setChecked(true);

    return  pToolbarMain;
}

void WeeklyReportDialog::ChangeActionChecked(WeeklyReportDialog::WeeklyReportDialogType type)
{
    m_pActionCommitReport->setChecked(false);
    m_pActionHistoryReport->setChecked(false);

    switch (type) {
    case    CommitDialog: m_pActionCommitReport->setChecked(true); return;
    default: m_pActionHistoryReport->setChecked(true); return;
    }
}
