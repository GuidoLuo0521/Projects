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

void WeeklyReportDialog::slotAccountChanged()
{
    slotCurrentDialogChanged(CommitDialog);
    emit signalAccountChange();
}

void WeeklyReportDialog::slotCurrentDialogChanged(WeeklyReportDialog::WeeklyReportDialogType type)
{
    ChangeActionChecked(type);
    m_pMainStackWidget->setCurrentIndex(type);
}

void WeeklyReportDialog::slotToolbarActionClicked(QAction * pAction)
{
    if(pAction == m_pActionCommitReport)
    {
        emit signalCurrentDialogChange(CommitDialog);
    }
    else if (pAction == m_pActionHistoryReport)
    {
        emit signalGetHistoryReport();
        emit signalCurrentDialogChange(HistoryDialog);
    }
}

void WeeklyReportDialog::InitLayout()
{
    QWidget* pToolBar = InitToolBar();

    QVBoxLayout * pMainLayout = new QVBoxLayout;
    m_pMainStackWidget = new QStackedWidget;

    ///////// Commit
    WeeklyReportCommitDialog * pCommitWidget = new WeeklyReportCommitDialog;
    m_pMainStackWidget->addWidget(pCommitWidget);

    ///////// History
    WeeklyReportHistoryDialog * pHistoryWidget = new WeeklyReportHistoryDialog;
    m_pMainStackWidget->addWidget(pHistoryWidget);
    connect(this, &WeeklyReportDialog::signalGetHistoryReport,
            pHistoryWidget, &WeeklyReportHistoryDialog::slotGetDate);

    pMainLayout->addWidget(pToolBar);
    pMainLayout->addWidget(m_pMainStackWidget);

    connect(this, &WeeklyReportDialog::signalCurrentDialogChange,
            this, &WeeklyReportDialog::slotCurrentDialogChanged);

    this->setLayout(pMainLayout);
}

QWidget* WeeklyReportDialog::InitToolBar()
{
    //QToolBar* pToolbarMain =  this->addToolBar("管理");
    QToolBar* pToolbarMain =  new QToolBar("管理");

    connect( pToolbarMain, &QToolBar::actionTriggered,
            this, &WeeklyReportDialog::slotToolbarActionClicked);

    pToolbarMain->setMovable(false);
    pToolbarMain->setFloatable(false);

    m_pActionCommitReport =  pToolbarMain->addAction("提交周报");
    m_pActionHistoryReport = pToolbarMain->addAction("历史周报");

    m_pActionCommitReport->setCheckable(true);
    m_pActionHistoryReport->setCheckable(true);

    m_pActionCommitReport->setChecked(true);

    return  pToolbarMain;
}

void WeeklyReportDialog::ChangeActionChecked(WeeklyReportDialog::WeeklyReportDialogType type)
{
    m_pActionCommitReport->setChecked(false);
    m_pActionHistoryReport->setChecked(false);

    switch (type) {
    case    HistoryDialog: m_pActionHistoryReport->setChecked(true); return;
    default: m_pActionCommitReport->setChecked(true); return;
    }
}
