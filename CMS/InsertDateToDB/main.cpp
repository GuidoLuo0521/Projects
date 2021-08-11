#include <QCoreApplication>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>
#include <QFile>
#include <QTextCodec>

#include "RandomParams.h"





int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase guidocms = QSqlDatabase::addDatabase("QMYSQL", "MySQL_GuidoCMS");
    guidocms.setHostName("127.0.0.1");
    guidocms.setPort(3306);
    guidocms.setDatabaseName("guidocms");
    guidocms.setUserName("root");
    guidocms.setPassword("millet");



    QStringList strListName;
    QFile file("D:/github/Projects/CMS/DevRecords/MySQL/name.txt");
    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        while (!stream.atEnd()) {
            strListName << stream.readLine();
        }

        file.close();
    }

    bool isV  = guidocms.isValid();
    //if(guidocms.open())
    {
        const int knCount = strListName.size();
        for( int i = 0; i < knCount; ++i)
        {
            int StaffID = 0;
            QString StaffName, StaffPassword;
            int Sex = 0;
            QString Birthday, Department, JobName;
            float Wage = 0.0;
            int WorkingAge = 0;
            QString Place, Education, Specialty, Address="00000000000", EMail="00000000000", Phone="00000000000", EnterCampany, LeaveCampany="0000-00-00", Introduction="暂无";
            int Resignation = 0;
            QString Param = "暂无";

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
                                     "VALUES ( %1, %2, %3, %4, %5, "
                                     "%6, %7, %8, %9, %10, "
                                     "%11, %12, %13, %14, %15, "
                                     "%16, %17, %18, %19, %20, %21);")
                    .arg(StaffID).arg(StaffName).arg(StaffPassword).arg(Sex).arg(Birthday)
                    .arg(Department).arg(JobName).arg(Wage).arg(WorkingAge).arg(Place)
                    .arg(Place).arg(Education).arg(Specialty).arg(Address).arg(EMail)
                    .arg(Phone).arg(EnterCampany).arg(LeaveCampany).arg(Introduction).arg(Resignation)
                    .arg(Param);

            qDebug() << strSql;

            //guidocms.exec(strSql);
            //qDebug() << guidocms.lastError().text();
        }

    }
    qDebug() << guidocms.lastError().text();

    return a.exec();
}
