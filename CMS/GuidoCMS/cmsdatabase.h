#ifndef GUIDOCMSDATABASE_H
#define GUIDOCMSDATABASE_H

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "singleton.h"

class CMSDatabase : public QSqlDatabase
{
public:
    CMSDatabase(
        const QString& type,
        const QString& connectionName,
        const QString& hostName,
        const QString& databaseName,
        const QString& userName,
        const QString& password );

    ~CMSDatabase();

private:
    const QString m_strType;
    const QString m_strConnectionName;
    const QString m_strHostName;
    const QString m_strDatabaseName;
    const QString m_strUserName;
    const QString m_strPassword;
};



#endif // GUIDOCMSDATABASE_H
