#ifndef JOBDATERDIALOG_H
#define JOBDATERDIALOG_H


#include "tabledatedialog.h"

class JobDateDialog : public TableDateDialog
{
public:
    JobDateDialog(QMainWindow * parent = 0);
    ~JobDateDialog();

protected:
    virtual void CreateSpecialDialog() override;

    virtual void InitSqlTableModel() override;
    virtual void InitSearchDialog() override;
    virtual void InitAddTableInfoDialog() override;

protected slots:
    virtual void slotFilter(QStringList) override;
};

#endif // TABLEJOBMANAGERDIALOG_H
