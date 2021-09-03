#ifndef STAFFPASSWORDDIALOG_H
#define STAFFPASSWORDDIALOG_H

#include <QDialog>
#include "common/staffinfo.h"

namespace Ui {
class StaffPasswordDialog;
}

class StaffPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StaffPasswordDialog(QWidget *parent = nullptr);
    ~StaffPasswordDialog();

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
