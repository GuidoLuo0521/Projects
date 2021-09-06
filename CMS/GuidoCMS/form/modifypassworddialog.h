#ifndef MODIFYPASSWORDDIALOG_H
#define MODIFYPASSWORDDIALOG_H

#include <QDialog>
#include "common/staffinfo.h"

namespace Ui {
class StaffPasswordDialog;
}

class ModifyPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPasswordDialog(QWidget *parent = nullptr);
    ~ModifyPasswordDialog();

signals:
    void signalUpdateSuccess();

private slots:
    void on_btnOK_clicked();

    void on_lineEditRawPassword_textChanged(const QString &arg1);

    void on_lineEditCheckPassword_textChanged(const QString &arg1);

    void on_lineEditNewPassword_textChanged(const QString &arg1);

private:
    int CheckParam();
    Ui::StaffPasswordDialog *ui;

    CStaffInfo * m_pCurrentStaff;
};

#endif // STAFFPASSWORDMANAGERDIALOG_H
