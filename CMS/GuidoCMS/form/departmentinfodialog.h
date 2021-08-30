#ifndef DEPARTMENTINFODIALOG_H
#define DEPARTMENTINFODIALOG_H

#include <QDialog>
#include <form/tableinfodialog.h>
#include "common/controlinclude.h"
#include "database/cmsdatabase.h"
#include "database/cmsdatebasedef.h"
#include <QSqlTableModel>

namespace Ui {
class DepartmentInfoDialog;
}

class DepartmentInfoDialog : public TableInfoDialog
{
    Q_OBJECT

public:
    explicit DepartmentInfoDialog(QWidget *parent = nullptr);
    ~DepartmentInfoDialog();

protected slots:
    void slotAdd();

protected:
    virtual void InitLayout() override;
    virtual void InitTableModel() override;
    virtual void InitTableView() override;

private:

    void InitDelegate();
    bool CheckParams();

private:
    Ui::DepartmentInfoDialog *ui;

    StanderLineEdit * m_pLineEditName;
    StanderComboBox * m_pComboBoxState;
    QPlainTextEdit * m_pPlainTextEditDesc;
};

#endif // DEPARTMENTINFODIALOG_H
