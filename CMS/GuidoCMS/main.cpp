#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

#include "CMSDef.h"


void LoadWebDatabase()
{
    // 网络数据库
    CMSDatabase * pWebDatabase = new CMSDatabase(
        gk_strWebDBType,
        gk_strWebDBConnectionName,
        gk_strWebDBHostName,
        gk_strWebDBDatabaseName,
        gk_strWebDBUserName,
        gk_strWebDBPassword);
    WebDatabaseSingleton::SetInstance(pWebDatabase);
    if(!pWebDatabase->open())
    {
        qDebug() << "网络数据库加载失败：" << pWebDatabase->lastError().text();
    }
    else
    {
        qDebug() << "网络数据库加载成功。";
    }
}

void Init()
{
    // 本地数据库
    CMSDatabase * pLocalDatabase = new CMSDatabase(
        gk_strLocalDBType,
        gk_strLocalDBConnectionName,
        gk_strLocalDBHostName,
        gk_strLocalDBDatabaseName,
        gk_strLocalDBUserName,
        gk_strLocalDBPassword);
    LocalDatabaseSingleton::SetInstance(pLocalDatabase);

    if(pLocalDatabase->open())
    {
        qDebug() << "本地数据库加载成功。";

        QSqlQuery query(*pLocalDatabase);
        QString strsql = QString::fromLocal8Bit("create table if not exists StaffInfo( "
                                                "staffid varchar(11), "
                                                "staffpassword varchar(10), "
                                                "remember bool, "
                                                "autolog bool);");
        if(!query.exec( strsql ) )
        {
            qDebug() << query.lastError().text();
        }
    }
    else
    {
        qDebug() << "本地数据库加载失败：" << pLocalDatabase->lastError().text();
    }

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Init();

    LoginDialog logindlg;
    logindlg.show();

    if(logindlg.exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.show();

        return a.exec();
    }
    else
        return 0;
}
