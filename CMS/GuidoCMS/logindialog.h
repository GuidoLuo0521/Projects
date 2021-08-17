#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "cmsdatabase.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    QString GetUserName();
    QString GetPassWord();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::LoginDialog *ui;

    int VerifyInput();


private:
    CMSDatabase * m_pCMSDatabase;
};

#endif // LOGINDIALOG_H
