#include "cmsdatabase.h"
#include "cmsdatebasedef.h"

/*
const QString CMSDatabase::m_strWebType = "QMYSQL";
const QString CMSDatabase::m_strWebConnectionName = "QMYSQL_WEBDB";
const QString CMSDatabase::m_strWebHostName = "127.0.0.1";
const QString CMSDatabase::m_strWebDatabaseName = "guidocms";
const QString CMSDatabase::m_strWebUserName = "root";
const QString CMSDatabase::m_strWebPassword = "";

const QString CMSDatabase::m_strLocalType = "QSQLITE";
const QString CMSDatabase::m_strLocalConnectionName = "QSQLITE_LOCALDB";
const QString CMSDatabase::m_strLocalHostName;
const QString CMSDatabase::m_strLocalDatabaseName = "cms.db";
const QString CMSDatabase::m_strLocalUserName ;
const QString CMSDatabase::m_strLocalPassword ;

QSqlDatabase CMSDatabase::m_WebDatabase;
QSqlDatabase CMSDatabase::m_LocalDatabase;

*/

CMSDatabase::CMSDatabase()
{
    InitParams();
    LoadDatabase();
}

CMSDatabase::~CMSDatabase()
{
    CloseDatabase();
}

bool CMSDatabase::WDB_IsOpen()
{
    return m_WebDatabase.isOpen();
}

bool CMSDatabase::LDB_IsOpen()
{
    return m_LocalDatabase.isOpen();
}

int CMSDatabase::WDB_VerifyLogin(const QString& strUsername, const QString& strPassword)
{
    //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败
    //连接数据库
    if(m_WebDatabase.isOpen())
    {
        //数据库操作
        QString strSQL = QString("SELECT %1 "
                                 "FROM %2 "
                                 "where %3 = '%4';")
                             .arg(CMSDB_Filed_Table_Staff::strStaffPassword)
                             .arg(CMSDB_Filed_Table_Staff::strStaffName)
                             .arg(CMSDB_Filed_Table_Staff::strStaffID)
                             .arg(strUsername);

        QSqlQuery query = m_WebDatabase.exec(strSQL);
        if(query.next())//遍历数据表
        {
            QString password=query.value("staffpassword").toString().trimmed();

            if((strPassword == password))
                return 1;
            else
                return 0;
        }

        return -1;
    }

    return  -2;
}

void CMSDatabase::InitParams()
{
    m_strWebType = "QMYSQL";
    m_strWebConnectionName = "QMYSQL_WEBDB";
    m_strWebHostName = "127.0.0.1";
    m_strWebDatabaseName = "guidocms";
    m_strWebUserName = "root";
    m_strWebPassword = "kangrulai";

    m_strLocalType = "QSQLITE";
    m_strLocalConnectionName = "QSQLITE_LOCALDB";
    m_strLocalHostName = "";
    m_strLocalDatabaseName = "cms.db";
    m_strLocalUserName = "";
    m_strLocalPassword = "";
}

void CMSDatabase::LoadDatabase()
{
    LoadWebDatabase();
    LoadLocalDatabase();
}

void CMSDatabase::LoadWebDatabase()
{
    // Web Database
    if (QSqlDatabase::contains(m_strWebConnectionName)) {
        m_WebDatabase = QSqlDatabase::database(m_strWebConnectionName);
    }
    else
    {
        m_WebDatabase = QSqlDatabase::addDatabase(m_strWebType, m_strWebConnectionName);
        m_WebDatabase.setHostName(m_strWebHostName);
        m_WebDatabase.setDatabaseName(m_strWebDatabaseName);
        m_WebDatabase.setUserName(m_strWebUserName);
        m_WebDatabase.setPassword(m_strWebPassword);

        if(m_WebDatabase.open())
            qDebug() << "Web Database Open Success.";
        else
            qDebug() << "Web Database Open Failed." << m_WebDatabase.lastError().text();
    }
}

void CMSDatabase::LoadLocalDatabase()
{
    // Local Database
    if (QSqlDatabase::contains(m_strLocalConnectionName)) {
        m_LocalDatabase = QSqlDatabase::database(m_strLocalConnectionName);
    }
    else
    {
        m_LocalDatabase = QSqlDatabase::addDatabase(m_strLocalType, m_strLocalConnectionName);
        m_LocalDatabase.setHostName(m_strLocalHostName);
        m_LocalDatabase.setDatabaseName(m_strLocalDatabaseName);
        m_LocalDatabase.setUserName(m_strLocalUserName);
        m_LocalDatabase.setPassword(m_strLocalPassword);

        if(m_LocalDatabase.open())
            qDebug() << "Local Database Open Success.";
        else
            qDebug() << "Local Database Open Failed." << m_LocalDatabase.lastError().text();
    }
}

void CMSDatabase::CloseDatabase()
{
    CloseWebDatabase();
    CloseLocalDatabase();
}

void CMSDatabase::CloseWebDatabase()
{
    if(m_WebDatabase.isOpen())
        m_WebDatabase.close();
}

void CMSDatabase::CloseLocalDatabase()
{

    if(m_LocalDatabase.isOpen())
        m_LocalDatabase.close();
}

QSqlQuery CMSDatabase::WDB_Exec(const QString& strQuery)
{
    return m_WebDatabase.exec(strQuery);
}
QSqlError CMSDatabase::WBD_LastError()
{
    return m_WebDatabase.lastError();
}
QSqlQuery CMSDatabase::LDB_Exec(const QString& strQuery)
{
    return m_LocalDatabase.exec(strQuery);
}
QSqlError CMSDatabase::LBD_LastError()
{
    return m_LocalDatabase.lastError();
}
