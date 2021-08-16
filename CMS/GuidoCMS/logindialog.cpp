#include "logindialog.h"
#include "ui_logindialog.h"
#include "CMSDef.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
    , ui(new Ui::LoginDialog)
    , m_pWebDatabase(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(360, 415);

    CMSDatabase * pWebDB = WebDatabaseSingleton::GetInstance();
    CMSDatabase * pLocalDB = LocalDatabaseSingleton::GetInstance();

    QString strErrorText = "";
    if(pWebDB->isOpen())
        m_pWebDatabase = pWebDB;
    else
        strErrorText += "WebDatabase Not Open。";

    if(pLocalDB->isOpen())
        m_pLocalDatabase = pLocalDB;
    else
        strErrorText += "LocalDatabase Not Open。";

    ui->labelInfo->setText(m_pWebDatabase && m_pLocalDatabase ? "已连接网络。" : strErrorText);
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
    if(m_pWebDatabase == nullptr)
        return;

    int nRetInput = VerificationInput();
    if(nRetInput == 1)
    {
        QString strUserName = QString::number(GetUserName().toInt());
        QString strPassWord = GetPassWord();

        int nRet = VerificationLogin(strUserName, strPassWord);
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
    if(m_pWebDatabase)
    {
       //数据库操作
       QString strSQL = QString("SELECT staffpassword FROM staff where staffid = %1;")
                            .arg(strUsername);

       QSqlQuery query = m_pWebDatabase->exec(strSQL);
       //if(query.isValid())
       {
           while(query.next())//遍历数据表
           {
                QString password=query.value("staffpassword").toString().trimmed();

                if((strPassword == password))
                    return 1;
                else
                    return 0;
           }

           return -1;
       }
    }

    return  -2;
}
