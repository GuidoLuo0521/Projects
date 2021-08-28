#include "common/commonapi.h"

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


CStaffInfo* GetStaffInfo(const QString& strStaffID)
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    CStaffInfo * pStaffInfo = new CStaffInfo;
    if(pDB->WDB_IsOpen())
    {
        QString sql = QString("SELECT * FROM staff Where staffid = %1").arg(strStaffID);
        QSqlQuery query = pDB->WDB_Exec(sql);
        if(query.next())
        {
            pStaffInfo->SetStaffID(strStaffID);
            pStaffInfo->SetStaffName(query.value("StaffName").toString());
            pStaffInfo->SetStaffPassword(query.value("StaffPassword").toString());
            pStaffInfo->SetBirthday(query.value("Birthday").toString());

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
