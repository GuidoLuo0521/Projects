#ifndef STAFFENTRYDIALOG_H
#define STAFFENTRYDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QSqlTableModel>
#include "common/staffinfo.h"
#include "database/cmsdatabase.h"
#include "form/entryadddialog.h"
#include "common/controlinclude.h"


class StaffEntryDialog : public EntryAddDialog
{
    Q_OBJECT

public:
    explicit StaffEntryDialog(QWidget *parent = nullptr);
    ~StaffEntryDialog();

signals:
    void signalAddSuccess(bool);

private slots:
    virtual void slotAdd() override;
    virtual void slotClear() override;

protected:
    virtual void InitLayout() override;

private:    
    void InsertStaff();
    bool CheckParams();
    bool CheckExist();

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
