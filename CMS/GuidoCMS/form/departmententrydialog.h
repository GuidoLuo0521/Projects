#ifndef DEPARTMENTENTRYDIALOG_H
#define DEPARTMENTENTRYDIALOG_H

#include <QDialog>
#include <form/entryadddialog.h>
#include "common/controlinclude.h"
#include "database/cmsdatabase.h"
#include "database/cmsdatebasedef.h"
#include <QSqlTableModel>


class DepartmentEntryDialog : public EntryAddDialog
{
    Q_OBJECT

public:
    explicit DepartmentEntryDialog(QWidget *parent = nullptr);
    ~DepartmentEntryDialog();

protected slots:
    virtual void slotAdd() override;
    virtual void slotClear() override;

protected:
    virtual void InitLayout() override;

private:
    bool CheckParams();

private:
    StanderLineEdit * m_pLineEditName;
    StanderComboBox * m_pComboBoxState;
    StanderPlainTextEdit * m_pPlainTextEditDesc;
};

#endif // DEPARTMENTINFODIALOG_H
