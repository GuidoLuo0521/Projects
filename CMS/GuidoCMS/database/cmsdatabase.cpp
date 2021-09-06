#include "cmsdatabase.h"
#include "cmsdatebasedef.h"

#include <QDateTime>
#include <QTcpSocket>

#include "common/ntpclient.h"

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
void CMSDatabase::InitParams()
{
    m_strWebType = "QMYSQL";
    m_strWebConnectionName = "QMYSQL_WEBDB";
    m_strWebHostName = "www.millet.fun";
    m_strWebDatabaseName = "guidocms";
    m_strWebUserName = "guido";
    m_strWebPassword = "123456";

    m_strLocalType = "QSQLITE";
    m_strLocalConnectionName = "QSQLITE_LOCALDB";
    m_strLocalHostName = "";
    m_strLocalDatabaseName = "cms.db";
    m_strLocalUserName = "";
    m_strLocalPassword = "";
}


CMSDatabase::CMSDatabase(QObject *parent)
    : QObject(parent)
{
    InitParams();
    LoadDatabase();

    //connect(NtpClient::Instance(), SIGNAL(receiveTime(QDateTime)), this, SLOT(slotReceiveTime(QDateTime)));
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

int CMSDatabase::WDB_VerifyLogin(const QString& strid, const QString& strPassword)
{
    //把登录信息的账号密码传进来，然后跟数据库进行比较，相同则验证成功，否则失败
    //连接数据库
    if(m_WebDatabase.isOpen())
    {
        //数据库操作
        QString strSQL = QString("SELECT %1 "
                                 "FROM %2 "
                                 "where %3 = '%4';")
                             .arg(g_listCMSDB_Table_Filed_Staff[Staff_StaffPassword])
                             .arg(g_listCMSDB_Table_Filed_Staff[Staff_StaffTableName])
                             .arg(g_listCMSDB_Table_Filed_Staff[Staff_StaffID])
                             .arg(strid);

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

QString CMSDatabase::WDB_Date(const QString& format)
{
    QSqlQuery query =  m_WebDatabase.exec("select now(3) as currentTime;");
    if(query.next())
    {
        return query.value("currentTime").toDateTime().toString(format);
    }

    return "0000-00-00";
}

QString CMSDatabase::WDB_WeekNumber()
{
    QString str = WDB_Date("yyyy-MM-dd");
    QString strw = QString("SELECT WEEK(date_add('%1',interval 6 day),2) AS weekNumber;").arg(str);
    QSqlQuery query = WDB_Exec(strw);
    if(query.next())
    {
        return query.value("weekNumber").toString();
    }

    return "";
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
            qDebug() << "Web database connect success.";
        else
            qDebug() << "Web database connect failed." << m_WebDatabase.lastError().text();
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
            qDebug() << "Local database connect success.";
        else
            qDebug() << "Local database connect failed." << m_LocalDatabase.lastError().text();


        QString strCTLog = "CREATE TABLE IF NOT EXISTS Log(   "
                                    "ID INTEGER PRIMARY KEY   AUTOINCREMENT,   "
                                    "Leave          TEXT    NOT NULL,   "
                                    "Date           TEXT    NOT NULL,   "
                                    "context        TEXT      );";

        LDB_Exec(strCTLog);

        QString strCTStaffinfo = "CREATE TABLE IF NOT EXISTS StaffInfo(   "
                                    "StaffID TEXT PRIMARY KEY  NOT NULL,   "
                                    "StaffPassword     TEXT    NOT NULL,"
                                    "RemenmberPW BOOL NOT NULL DEFAULT FALSE,"
                                    "AutoLogin BOOL NOT NULL DEFAULT FALSE,"
                                    "ActiveState BOOL NOT NULL DEFAULT TRUE,"
                                    "SelectState BOOL NOT NULL DEFAULT FALSE);";

        LDB_Exec(strCTStaffinfo);

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

QString CMSDatabase::slotReceiveTime(const QDateTime &dateTime)
{
    return dateTime.toString("yyyy-MM-dd HH:mm:ss.zzz");
}


QSqlQuery CMSDatabase::WDB_Exec(const QString& strQuery)
{
    return m_WebDatabase.exec(strQuery);
}
QSqlError CMSDatabase::WDB_LastError()
{
    return m_WebDatabase.lastError();
}
QSqlQuery CMSDatabase::LDB_Exec(const QString& strQuery)
{
    return m_LocalDatabase.exec(strQuery);
}
QSqlError CMSDatabase::LDB_LastError()
{
    return m_LocalDatabase.lastError();
}

QSqlQuery CMSDatabase::LDB_Log(const QString &leave, const QString &context)
{
    QString strTimeStamp;

#if 0
    //    NtpClient::Instance()->getDateTime();

#elif 0
    QString strUrl = "128.138.141.172";
    //QString strUrl = "http://www.ntsc.ac.cn/";
    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost(strUrl, 13);
    if (socket->waitForConnected())
    {
        if (socket->waitForReadyRead())
        {
            QString str(socket->readAll());
            str = str.trimmed();
            str = str.section(" ", 1, 2);
            str = "20" + str;

            QDateTime date = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss.zzz");
            date = date.toLocalTime();
            str = date.toString("yyyy-MM-dd hh:mm:ss.zzz");
        }
    }
    socket->close();
    delete socket;
#elif 1

    QSqlQuery query =  m_WebDatabase.exec("select now(3) as currentTime;");
    if(query.next())
    {
        strTimeStamp = query.value("currentTime").toDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    }

#elif 0
    // 这里应该获取服务器时间，本地时间可能改变
    strTimeStamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

#endif

    QString strQuery = QString("INSERT INTO Log(Date, Leave, Context) "
                               "VALUES('%1', '%2', '%3')")
                           .arg(strTimeStamp).arg(leave).arg(context);


    return LDB_Exec(strQuery);
}

QSqlQuery CMSDatabase::LDB_Log_FATAL(const QString& context)
{
    return LDB_Log("FATAL", context);
}
QSqlQuery CMSDatabase::LDB_Log_ERROR(const QString& context)
{
    return LDB_Log("ERROR", context);
}
QSqlQuery CMSDatabase::LDB_Log_WARN(const QString& context)
{
    return LDB_Log("WARN", context);
}
QSqlQuery CMSDatabase::LDB_Log_INFO(const QString& context)
{
    return LDB_Log("INFO", context);
}
QSqlQuery CMSDatabase::LDB_Log_DEBUG(const QString& context)
{
    return LDB_Log("DEBUG", context);
}
QSqlQuery CMSDatabase::LDB_Log_TRACE(const QString& context)
{
    return LDB_Log("TRACE", context);
}

