#include "logindialog.h"
#include "ui_logindialog.h"


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
    , ui(new Ui::LoginDialog)
    , m_pCMSDatabase(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(360, 450);

    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();

    QString strErrorText = pDB ? "网络已连接。\n" : "网络未连接。\n";
    if( pDB )
    {
        if(!pDB->WDB_IsOpen())
            strErrorText += "WebDatabase Not Open。\n";

        if(!pDB->LDB_IsOpen())
            strErrorText += "LocalDatabase Not Open。\n";
    }

    ui->labelInfo->setText(strErrorText);

    m_pCMSDatabase = pDB;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::GetUserName()
{
    return ui->leUserName->text();
}

QString LoginDialog::GetPassWord()
{
    return ui->lePassword->text();
}

void LoginDialog::on_btnLogin_clicked()
{
    if(m_pCMSDatabase == nullptr)
        return;

    int nRetInput = VerifyInput();
    if(nRetInput == 1)
    {
        QString strUserName = GetUserName();
        QString strPassWord = GetPassWord();

        int nRet = m_pCMSDatabase->WDB_VerifyLogin(strUserName, strPassWord);
        if(nRet == 1)
        {
            accept();
        }
        else if(nRet == -1)
        {
            QMessageBox::warning(this, "警告", "暂无此用户！");

            ui->lePassword->clear();
            ui->leUserName->setFocus();
        }
        else if( nRet == 0)
        {
            QMessageBox::warning(this, "警告", "密码错误！");

            ui->lePassword->clear();
            ui->lePassword->setFocus();
        }
    }
    else if(nRetInput == -1)
    {
        QMessageBox::warning(this, "警告", "用户名不能为空！");
    }
    else if(nRetInput == 0)
    {
        QMessageBox::warning(this, "警告", "密码不能为空！");
    }
}

int LoginDialog::VerifyInput()
{
    QString strUserName = GetUserName();
    QString strPassWord = GetPassWord();
    if(strUserName.isEmpty())
    {
        return -1;
    }
    if(strPassWord.isEmpty())
    {
        return  0;
    }

    return  1;
}


