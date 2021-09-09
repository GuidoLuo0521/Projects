#ifndef MODIFYPASSWORDDIALOG_H
#define MODIFYPASSWORDDIALOG_H

#include <QDialog>
#include "common/staffinfo.h"

namespace Ui {
class ProfileDialog;
}

class ProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileDialog(QWidget *parent = nullptr);
    ~ProfileDialog();

signals:
    void signalUpdateSuccess();

private slots:
    void on_btnOK_clicked();

    void on_lineEditRawPassword_textChanged(const QString &arg1);

    void on_lineEditCheckPassword_textChanged(const QString &arg1);

    void on_lineEditNewPassword_textChanged(const QString &arg1);

private:
    int CheckParam();
    Ui::ProfileDialog *ui;

    CStaffInfo * m_pCurrentStaff;
};

#endif // STAFFPASSWORDMANAGERDIALOG_H
