#ifndef WEEKLYREPORTHISTORYDIALOG_H
#define WEEKLYREPORTHISTORYDIALOG_H

#include "common/controlinclude.h"
#include "controlext/controlext.h"

#include <QNetworkAccessManager>

class WeeklyReportHistoryDialog : public QWidget
{
    Q_OBJECT
public:
    explicit WeeklyReportHistoryDialog(QWidget *parent = nullptr);

signals:

public slots:
    void slotGetDate();
    void slotAccountChanged();

protected:
    void InitLayout();
private:
    QTableView * m_pTableView;
    QStandardItemModel * m_pStandardItemModel;

    QNetworkAccessManager * m_pNetManager;
};

#endif // WEEKLYREPORTHISTORYDIALOG_H
