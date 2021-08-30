#ifndef STAFFINFODIALOG_H
#define STAFFINFODIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QSqlTableModel>
#include "common/staffinfo.h"
#include "database/cmsdatabase.h"
#include "form/tableinfodialog.h"
#include "common/controlinclude.h"

namespace Ui {
class StaffInfoDialog;
}

class StaffInfoDialog : public TableInfoDialog
{
    Q_OBJECT

public:
    // 如果为空，则为增加，不为空，则为修改
    explicit StaffInfoDialog(QWidget *parent = nullptr);
    ~StaffInfoDialog();

protected:
    virtual void InitLayout() override;
    virtual void InitTableView() override;
    virtual void InitTableModel() override;


private:    
    void InsertStaff();
    bool CheckParams();

private:
    Ui::StaffInfoDialog *ui;

private:
    StanderLineEdit * m_pLineEditName;
    StanderLineEdit * m_pLineEditPassword;
    StanderLineEdit * m_pLineEditWorkingAge;
    StanderLineEdit * m_pLineEditWage;
    StanderLineEdit * m_pLineEditPhone;
    StanderLineEdit * m_pLineEditEmail;
    StanderLineEdit * m_pLineEditAddress;

    StanderComboBox * m_pComboBoxSex;
    StanderComboBox * m_pComboBoxPlace;
    StanderComboBox * m_pComboBoxDepartment;
    StanderComboBox * m_pComboBoxJob;
    StanderComboBox * m_pComboBoxEducation;
    StanderComboBox * m_pComboBoxSpecialty;

    StanderDateEdit * m_pDateEditBirthday;
    StanderDateEdit * m_pDateEditEnterCompany;
    StanderDateEdit * m_pDateEditLeaveCompany;

    StanderPlainTextEdit * m_pPlainTextEditDesc;

};

#endif // STAFFINFODIALOG_H
