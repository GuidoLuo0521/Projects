#ifndef TABLEJOBMANAGERDIALOG_H
#define TABLEJOBMANAGERDIALOG_H

#include "tablemanagerdialog.h"

class TableJobManagerDialog : public TableManagerDialog
{
public:
    TableJobManagerDialog(QMainWindow * parent = 0);
    ~TableJobManagerDialog();

protected:
    virtual void CreateSpecialDialog() override;

    virtual void InitLayout() override;
    virtual void InitSqlTableModel() override;
    virtual void InitSearchDialog() override;
    virtual void InitAddTableInfoDialog() override;

protected slots:
    virtual void slotFilter(QStringList) override;
};

#endif // TABLEJOBMANAGERDIALOG_H
