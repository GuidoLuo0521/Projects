#ifndef GUIDOCMSDATABASE_H
#define GUIDOCMSDATABASE_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>

#include "common/singleton.h"


class CMSDatabase : QObject
{
    Q_OBJECT
public:
    CMSDatabase(QObject *parent = nullptr);
    ~CMSDatabase();

    bool WDB_IsOpen();
    bool LDB_IsOpen();

    /// 登录检查
    /// 返回值  1：成功，0：密码错误 -1：没此账户 2：数据库未连接
    int WDB_VerifyLogin(const QString& strUsername, const QString& strPassword);

    QString WDB_Date(const QString& format);
    QString WDB_WeekNumber();

    QSqlQuery WDB_Exec(const QString& strQuery);
    QSqlError WDB_LastError();

    QSqlQuery LDB_Exec(const QString& strQuery);
    QSqlError LDB_LastError();

    QSqlQuery LDB_Log(const QString& leave, const QString& context);
    QSqlQuery LDB_Log_FATAL(const QString& context);
    QSqlQuery LDB_Log_ERROR(const QString& context);
    QSqlQuery LDB_Log_WARN(const QString& context);
    QSqlQuery LDB_Log_INFO(const QString& context);
    QSqlQuery LDB_Log_DEBUG(const QString& context);
    QSqlQuery LDB_Log_TRACE(const QString& context);


    QSqlDatabase m_WebDatabase;
    QSqlDatabase m_LocalDatabase;

private:
    void InitParams();

    void LoadDatabase();
    void LoadWebDatabase();
    void LoadLocalDatabase();

    void CloseDatabase();
    void CloseWebDatabase();
    void CloseLocalDatabase();

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

signals:
    void WriteLog();

private slots:
    QString slotReceiveTime(const QDateTime &dateTime);
};

typedef Singleton<CMSDatabase> CMSDatabaseSingleton;


#endif // GUIDOCMSDATABASE_H
