#ifndef TABLEROLEMANAGERDIALOG_H
#define TABLEROLEMANAGERDIALOG_H

#include "tablemanagerdialog.h"

class TableRoleManagerDialog : public TableManagerDialog
{
public:
    TableRoleManagerDialog(QMainWindow * parent = 0);
    ~TableRoleManagerDialog();

protected:
    virtual void CreateSpecialDialog() override;

    virtual void InitLayout() override;
    virtual void InitSqlTableModel() override;
    virtual void InitSearchDialog() override;
    virtual void InitAddTableInfoDialog() override;

protected slots:
    virtual void slotFilter(QStringList) override;

};

#endif // TABLEROLEMANAGERDIALOG_H
