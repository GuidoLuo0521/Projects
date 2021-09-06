#ifndef DEPARTMENTDATEDIALOG_H
#define DEPARTMENTDATEDIALOG_H

#include "tabledatedialog.h"

class DepartmentDateDialog : public TableDateDialog
{
public:
    DepartmentDateDialog(QMainWindow * parent = 0);
    ~DepartmentDateDialog();

protected:
    virtual void CreateSpecialDialog() override;

    virtual void InitSqlTableModel() override;
    virtual void InitSearchDialog() override;
    virtual void InitAddTableInfoDialog() override;

protected slots:
    virtual void slotFilter(QStringList) override;

};

#endif // TABLEDEPARTMENTMANAGERDIALOG_H
