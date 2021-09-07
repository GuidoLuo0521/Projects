#ifndef WEEKLYREPORTCOMMITDIALOG_H
#define WEEKLYREPORTCOMMITDIALOG_H

#include "common/controlinclude.h"
#include "controlext/controlext.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class WeeklyReportCommitDialog : public QWidget
{
    Q_OBJECT
public:
    explicit WeeklyReportCommitDialog(QWidget *parent = nullptr);

signals:

private slots:
    void slotCommit();
    void slotClear();
    void slotRequestFinished(QNetworkReply *reply);

protected:
    void InitLayout();


private:
    StanderLineEdit * m_pProjectName;
    StanderPlainTextEdit * m_pFinishEdit;
    StanderPlainTextEdit * m_pPlanEdit ;

    QNetworkAccessManager* m_pNetworkManager;
};

#endif // WEEKLYREPORTCOMMITDIALOG_H
