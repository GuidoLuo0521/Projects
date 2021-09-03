#ifndef TABLEDEPARTMENTMANAGERDIALOG_H
#define TABLEDEPARTMENTMANAGERDIALOG_H

#include "tablemanagerdialog.h"

class TableDepartmentManagerDialog : public TableManagerDialog
{
public:
    TableDepartmentManagerDialog(QMainWindow * parent = 0);
    ~TableDepartmentManagerDialog();

protected:
    virtual void CreateSpecialDialog() override;

    virtual void InitSqlTableModel() override;
    virtual void InitSearchDialog() override;
    virtual void InitAddTableInfoDialog() override;

protected slots:
    virtual void slotFilter(QStringList) override;

};

#endif // TABLEDEPARTMENTMANAGERDIALOG_H
