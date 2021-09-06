#include "common/commonapi.h"
#include <QNetworkInterface>
#include <QList>

void InitGlobalParams()
{
    LoadDatabaseSingleton();

    //CreateCurrentStaffInfoSingleton();
}

void LoadDatabaseSingleton()
{
    CMSDatabaseSingleton::SetInstance(new CMSDatabase());
}

void CreateCurrentStaffInfoSingleton()
{
    StaffInfoSingleton::SetInstance(new CStaffInfo);
}


CStaffInfo* GetStaffInfo(const QString& strStaffID, const QString& strStaffPassWord)
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    CStaffInfo * pStaffInfo = new CStaffInfo;
    if(pDB->WDB_IsOpen())
    {
        QString sql = QString("SELECT * FROM staff Where staffid = %1 AND StaffPassword = '%2'")
                          .arg(strStaffID).arg(strStaffPassWord);
        QSqlQuery query = pDB->WDB_Exec(sql);
        if(query.next())
        {
            pStaffInfo->SetStaffID(strStaffID);
            pStaffInfo->SetStaffName(query.value("StaffName").toString());
            pStaffInfo->SetStaffPassword(query.value("StaffPassword").toString());
            pStaffInfo->SetBirthday(query.value("Birthday").toString());
            pStaffInfo->SetSex(query.value("Sex").toString());

            pStaffInfo->SetDepartment(query.value("Department").toString());
            pStaffInfo->SetJobName(query.value("JobName").toString());
            pStaffInfo->SetWage(query.value("Wage").toFloat());

            pStaffInfo->SetWorkingAge(query.value("WorkingAge").toInt());
            pStaffInfo->SetPlace(query.value("Place").toString());
            pStaffInfo->SetEducation(query.value("Education").toString());
            pStaffInfo->SetSpecialty(query.value("Specialty").toString());
            pStaffInfo->SetAddress(query.value("Address").toString());
            pStaffInfo->SetEmail(query.value("Email").toString());
            pStaffInfo->SetPhone(query.value("Phone").toString());
            pStaffInfo->SetEnterCompany(query.value("EnterCompany").toString());
            pStaffInfo->SetLeaveCompany(query.value("LeaveCompany").toString());
            pStaffInfo->SetIntroduction(query.value("Introduction").toString());
            pStaffInfo->SetParam(query.value("Params").toString());

            return  pStaffInfo;
        }
    }

    return nullptr;
}




QString GetIPPath()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
        {
            strIpAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // 如果没有找到，则以本地IP地址为IP
    if (strIpAddress.isEmpty())
    {
        qDebug() << strIpAddress;
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    //qDebug() << "IP:" << strIpAddress;
    return strIpAddress;
}

QString GetMacPath()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表

    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) &&
                nets[i].flags().testFlag(QNetworkInterface::IsRunning) &&
                !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }

    //qDebug() << "Mac:" << strMacAddr;
    return strMacAddr;
}
