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
        HistoryDialog,
        CommitDialog,
    };


public:
    explicit WeeklyReportDialog(QWidget *parent = nullptr);
    ~WeeklyReportDialog();

signals:
    void signalShowCurrentDialog(WeeklyReportDialogType);

private:
    void slotShowDialog(WeeklyReportDialogType);
    void slotToolbarActionClicked();

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
