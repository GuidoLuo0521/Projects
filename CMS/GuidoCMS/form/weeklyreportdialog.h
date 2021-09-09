#ifndef WEEKLYREPORTDIALOG_H
#define WEEKLYREPORTDIALOG_H

#include "common/controlinclude.h"
#include "form/cmsbasewidget.h"
#include "controlext/controlext.h"

class WeeklyReportDialog : public CMSBaseWidget
{
    Q_OBJECT
    enum WeeklyReportDialogType
    {
        CommitDialog,
        HistoryDialog,
    };


public:
    explicit WeeklyReportDialog(QWidget *parent = nullptr);
    ~WeeklyReportDialog();

public slots:
    void slotAccountChanged();

signals:
    void signalAccountChange();
    void signalCurrentDialogChange(WeeklyReportDialogType);
    void signalGetHistoryReport();

private slots:
    void slotCurrentDialogChanged(WeeklyReportDialogType);
    void slotToolbarActionClicked(QAction * pAction);

protected:
    virtual void InitLayout() override;
    QWidget* InitToolBar();
    void ChangeActionChecked(WeeklyReportDialogType type);

private:
    QStackedWidget  * m_pMainStackWidget;
    QAction  * m_pActionHistoryReport;
    QAction  * m_pActionCommitReport;
};

#endif // WEEKLYREPORTDIALOG_H
