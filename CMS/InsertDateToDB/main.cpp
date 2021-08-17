#include <QCoreApplication>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>
#include <QFile>
#include <QTextCodec>

#include "RandomParams.h"


void InsertStaff( QSqlDatabase& guidocms)
{
    if(guidocms.isOpen())
    {
        QStringList strListName;
        QString strFilePath = "D:/github/Projects/CMS/DevRecords/MySQL/name.txt";
        QFile file(strFilePath);
        if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            QTextStream stream(&file);
            stream.setCodec("UTF-8");

            while (!stream.atEnd()) {
                strListName << stream.readLine();
            }

            file.close();
        }

        const int knCount = strListName.size();
        for( int i = 0; i < knCount; ++i)
        {
            int StaffID = 0;
            QString StaffName, StaffPassword;
            int Sex = 0;
            QString Birthday, Department, JobName;
            float Wage = 0.0;
            int WorkingAge = 0;
            QString Place, Education, Specialty, Address="", EMail="", Phone="",
                    EnterCampany, LeaveCampany="0000-00-00", Introduction="";
            int Resignation = 0;
            QString Param = "";

            StaffID = 0;
            StaffName = strListName[i];
            StaffPassword = GetRandomPassword();
            Sex = GetRandomSex();
            Birthday = GetRandomBirthday();
            Department = GetRandomDepartent();
            JobName = Department;
            JobName.remove("部");
            JobName.remove("科");

            Wage = GetRandomWage();
            WorkingAge = GetRandomWorkingAge();

            Place = GetRandomPlace();
            Education = GetRandomEducation();
            if(Education != "小学" && Education != "初中" && Education != "高中")
            {
                Specialty = GetRandomSpecialty();
            }

            EnterCampany = GetRandomEnterCompany();
            Resignation = GetRandomResignation();

            QString strSql = QString(" INSERT INTO staff "
                                     "VALUES (%1,'%2','%3',%4,'%5',"
                                     "'%6','%7',%8,%9,'%10',"
                                     "'%11','%12','%13','%14','%15',"
                                     "'%16','%17','%18',%19,'%20');")
                    .arg(StaffID).arg(StaffName).arg(StaffPassword).arg(Sex).arg(Birthday)
                    .arg(Department).arg(JobName).arg(Wage).arg(WorkingAge).arg(Place)
                    .arg(Education).arg(Specialty).arg(Address).arg(EMail).arg(Phone)
                    .arg(EnterCampany).arg(LeaveCampany).arg(Introduction).arg(Resignation).arg(Param);

            guidocms.exec(strSql);
            strSql = "SELECT last_insert_id() AS 'Account';";
            QSqlQuery query = guidocms.exec(strSql);

            while (query.next()) {
               qDebug() << QString("%1").arg(query.value("Account").toInt(), 6, 10, QLatin1Char('0'));
            }
        }
    }

    qDebug() << "InsertStaff exec end.";
}

void InsertDepartment(QSqlDatabase& guidocms)
{
    if(guidocms.isOpen())
    {
        const int knCount = g_strListDepartment.size();
        for( int i = 0; i < knCount; ++i)
        {
            int DepartmntID = 0, State = 1;
            QString DepartmentName = g_strListDepartment[i], Description, Param;

            QString strSql = QString(" INSERT INTO department "
                                     "(DepartmntID, DepartmentName, State, Description, Param)"
                                     "VALUES (%1,'%2', %3,'%4', '%5');")
                    .arg(DepartmntID).arg(DepartmentName).arg(State).arg(Description).arg(Param);

            guidocms.exec(strSql);
        }
    }
}

void InsertJob(QSqlDatabase& guidocms)
{
    if(guidocms.isOpen())
    {
        const int knCount = g_strListDepartment.size();
        for( int i = 0; i < knCount; ++i)
        {
            int JobID = 0, State = 1;
            float BasicWage = GetRandomWage();
            QString JobName = g_strListDepartment[i], Description, Param;
            JobName.remove("部");
            JobName.remove("科");

            QString strSql = QString(" INSERT INTO job "
                                     "(JobID, JobName, State, BasicWage, Description, Param)"
                                     "VALUES (%1,'%2', %3, %4,'%5','%6');")
                    .arg(JobID).arg(JobName).arg(State).arg(BasicWage).arg(Description).arg(Param);

            guidocms.exec(strSql);
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase guidocms = QSqlDatabase::addDatabase("QMYSQL", "MySQL_GuidoCMS");
    guidocms.setHostName("127.0.0.1");
    guidocms.setPort(3306);
    guidocms.setDatabaseName("guidocms");
    guidocms.setUserName("root");
    guidocms.setPassword("");

    guidocms.open();

    //InsertStaff(guidocms);

    //InsertDepartment(guidocms);

    //InsertJob(guidocms);

    guidocms.close();

    return a.exec();
}
