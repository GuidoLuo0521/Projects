#ifndef WEEKLYREPORTCOMMITDIALOG_H
#define WEEKLYREPORTCOMMITDIALOG_H

#include "common/controlinclude.h"
#include "controlext/controlext.h"

class WeeklyReportCommitDialog : public QWidget
{
    Q_OBJECT
public:
    explicit WeeklyReportCommitDialog(QWidget *parent = nullptr);

signals:

private slots:
    void slotCommit();
    void slotClear();

protected:
    void InitLayout();

private:
    StanderLineEdit * m_pProjectName;
    StanderPlainTextEdit * m_pFinishEdit;
    StanderPlainTextEdit * m_pPlanEdit ;
};

#endif // WEEKLYREPORTCOMMITDIALOG_H
