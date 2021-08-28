#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "database/cmsdatabase.h"

namespace Ui {
class LoginDialog;
}


struct LoginStaff
{
    QString strStaffID;
    QString strPassword;
    bool bRemenmberPW;
    bool bAutoLogin;
    bool bActiveState;
    bool bSelectState;

    LoginStaff()
    {
        bActiveState = true;
        strStaffID = strPassword = "";
        bRemenmberPW = bAutoLogin = bSelectState = false;
    }
};


class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    QString GetUserID();
    QString GetPassWord();

public slots:
    void slotShowMainWindow();

signals:
    void signalShowMainWindow();

private slots:

    void on_btnLogin_clicked();

    void on_cbUserName_currentIndexChanged(int index);

    void on_checkBoxAutoLogin_clicked(bool checked);

    void on_leUserName_textChanged(const QString &arg1);

private:
    int VerifyInput();

    void UpdateCombox();

    // 更新登录人员信息
    int UpdateStaffInfo(const QString &strPassWord, const bool bRemenmberPW, const bool bAutoLogin, const bool bState );

    int LoadLocalStaffInfo();
    void Clear();

    bool CheckExistStaff(const QString &strUID);

private:
    Ui::LoginDialog *ui;
    CMSDatabase * m_pCMSDatabase;

    int m_nSelectStaffIndex ;
    int m_nCurrentStaffIndex ;
    QList<LoginStaff> m_listLoginStaffs;
};

#endif // LOGINDIALOG_H
