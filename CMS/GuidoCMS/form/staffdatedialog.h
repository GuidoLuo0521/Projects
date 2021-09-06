#ifndef STAFFDATEDIALOG_H
#define STAFFDATEDIALOG_H

#include "tabledatedialog.h"

class StaffDateDialog : public TableDateDialog
{
public:
    StaffDateDialog(QMainWindow * parent = 0);

protected:
    virtual void CreateSpecialDialog() override;

    virtual void InitSqlTableModel() override;
    virtual void InitSearchDialog() override;
    virtual void InitAddTableInfoDialog() override;

protected slots:
    virtual void slotFilter(QStringList) override;
};

#endif // TABLESTAFFMANAGERDIALOG_H
