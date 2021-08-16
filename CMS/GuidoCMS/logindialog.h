#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "CMSDef.h"

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

    int VerificationInput();
    int VerificationLogin(const QString& strUsername, const QString& strPassword);

private:
    CMSDatabase * m_pWebDatabase;
    CMSDatabase * m_pLocalDatabase;
};

#endif // LOGINDIALOG_H
