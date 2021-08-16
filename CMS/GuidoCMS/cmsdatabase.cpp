#include "cmsdatabase.h"


CMSDatabase::CMSDatabase(
    const QString &type,
    const QString &connectionName,
    const QString &hostName,
    const QString &databaseName,
    const QString &userName,
    const QString &password)
: m_strType(type)
, m_strConnectionName(connectionName)
, m_strHostName(hostName)
, m_strDatabaseName(databaseName)
, m_strUserName(userName)
, m_strPassword(password)
{
    if (QSqlDatabase::contains(m_strConnectionName)) {
        *(QSqlDatabase*)this = QSqlDatabase::database(m_strConnectionName);
    }
    else
    {
        *(QSqlDatabase*)this = QSqlDatabase::addDatabase(m_strType, m_strConnectionName);

        this->setHostName(m_strHostName);
        this->setDatabaseName(m_strDatabaseName);
        this->setUserName(m_strUserName);
        this->setPassword(m_strPassword);
    }
}

CMSDatabase::~CMSDatabase()
{
    if(this->isOpen())
        this->close();
}
