#ifndef GUIDOCMSDATABASE_H
#define GUIDOCMSDATABASE_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "singleton.h"

class CMSDatabase
{
public:
    CMSDatabase();
    ~CMSDatabase();

    bool WDB_IsOpen();
    bool LDB_IsOpen();

    /// 登录检查
    /// 返回值  1：成功，0：密码错误 -1：没此账户 2：数据库未连接
    int WDB_VerifyLogin(const QString& strUsername, const QString& strPassword);

    QSqlQuery WDB_Exec(const QString& strQuery);
    QSqlError WBD_LastError();

    QSqlQuery LDB_Exec(const QString& strQuery);
    QSqlError LBD_LastError();

private:
    void InitParams();

    void LoadDatabase();
    void LoadWebDatabase();
    void LoadLocalDatabase();

    void CloseDatabase();
    void CloseWebDatabase();
    void CloseLocalDatabase();

    QSqlDatabase m_WebDatabase;
    QSqlDatabase m_LocalDatabase;

    QString m_strWebType;
    QString m_strWebConnectionName;
    QString m_strWebHostName;
    QString m_strWebDatabaseName;
    QString m_strWebUserName;
    QString m_strWebPassword;

    QString m_strLocalType;
    QString m_strLocalConnectionName;
    QString m_strLocalHostName;
    QString m_strLocalDatabaseName;
    QString m_strLocalUserName;
    QString m_strLocalPassword;
};

typedef Singleton<CMSDatabase> CMSDatabaseSingleton;


#endif // GUIDOCMSDATABASE_H
