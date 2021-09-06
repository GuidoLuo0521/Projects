#ifndef ROLEDATEDIALOG_H
#define ROLEDATEDIALOG_H

#include "tabledatedialog.h"

class RoleDateDialog : public TableDateDialog
{
public:
    RoleDateDialog(QMainWindow * parent = 0);
    ~RoleDateDialog();

protected:
    virtual void CreateSpecialDialog() override;

    virtual void InitSqlTableModel() override;
    virtual void InitSearchDialog() override;
    virtual void InitAddTableInfoDialog() override;

protected slots:
    virtual void slotFilter(QStringList) override;

};

#endif // TABLEROLEMANAGERDIALOG_H
