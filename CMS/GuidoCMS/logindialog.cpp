#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
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
    int nRetInput = VerificationInput();
    if(nRetInput == 1)
    {
        QString strUserName = QString::number(GetUserName().toInt());
        QString strPassWord = GetPassWord();

        int nRet = VerificationLogin(strUserName, strPassWord);
        if(nRet == 1)
            accept();
        else if(nRet == -1)
        {
            QMessageBox::warning(this, "警告", "暂无此用户！");

            ui->leUserName->clear();
            ui->lePassword->clear();
            ui->leUserName->setFocus();
        }
        else
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

int LoginDialog::VerificationInput()
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

int LoginDialog::VerificationLogin(const QString& strUsername, const QString& strPassword)
{
    //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败
    //连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "MySQL_guidocms");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("guidocms");
    db.setUserName("root");
    db.setPassword("");

    if(db.open())
    {
       //数据库操作
       QSqlQuery query(db);
       QString strSQL = QString("SELECT staffpassword FROM staff where staffid = %1;").arg(strUsername);

       if(query.exec(strSQL))
       {
           while(query.next())//遍历数据表
           {
                QString password=query.value("staffpassword").toString().trimmed();

                if((strPassword == password))
                    return 1;
           }

           db.close();
       }
       return -1;

    }
    return 0;
}
