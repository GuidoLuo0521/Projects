#ifndef ADDDEPARTMENTINFODIALOG_H
#define ADDDEPARTMENTINFODIALOG_H

#include <QDialog>
#include <form/addtableinfodialog.h>
#include "common/controlinclude.h"
#include "database/cmsdatabase.h"
#include "database/cmsdatebasedef.h"
#include <QSqlTableModel>


class AddTableInfoDepartmentDialog : public AddTableInfoDialog
{
    Q_OBJECT

public:
    explicit AddTableInfoDepartmentDialog(QWidget *parent = nullptr);
    ~AddTableInfoDepartmentDialog();

signals:
    void signalAddSuccess(bool);

protected slots:
    virtual void slotAdd() override;
    virtual void slotClear() override;

protected:
    virtual void InitLayout() override;

private:

    void InitDelegate();
    bool CheckParams();

private:
    StanderLineEdit * m_pLineEditName;
    StanderComboBox * m_pComboBoxState;
    StanderPlainTextEdit * m_pPlainTextEditDesc;
};

#endif // DEPARTMENTINFODIALOG_H
