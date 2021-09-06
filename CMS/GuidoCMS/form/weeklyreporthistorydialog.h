#ifndef WEEKLYREPORTHISTORYDIALOG_H
#define WEEKLYREPORTHISTORYDIALOG_H

#include "common/controlinclude.h"
#include "controlext/controlext.h"

class WeeklyReportHistoryDialog : public QWidget
{
    Q_OBJECT
public:
    explicit WeeklyReportHistoryDialog(QWidget *parent = nullptr);

signals:


protected:
    void InitLayout();
    void AddDate();

private:
    QTableView * m_pTableView;
    QStandardItemModel * m_pStandardItemModel;

};

#endif // WEEKLYREPORTHISTORYDIALOG_H
