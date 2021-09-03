#ifndef TABLESTAFFMANAGERDIALOG_H
#define TABLESTAFFMANAGERDIALOG_H

#include "tablemanagerdialog.h"

class TableStaffManagerDialog : public TableManagerDialog
{
public:
    TableStaffManagerDialog(QMainWindow * parent = 0);

protected:
    virtual void CreateSpecialDialog() override;

    virtual void InitSqlTableModel() override;
    virtual void InitSearchDialog() override;
    virtual void InitAddTableInfoDialog() override;

protected slots:
    virtual void slotFilter(QStringList) override;
};

#endif // TABLESTAFFMANAGERDIALOG_H
