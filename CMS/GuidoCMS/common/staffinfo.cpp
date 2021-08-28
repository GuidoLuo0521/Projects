#include "common/staffinfo.h"

#include <QDateTime>

CStaffInfo::CStaffInfo()
{

}
CStaffInfo::~CStaffInfo()
{

}

void CStaffInfo::InitParams()
{
    m_strStaffID = "-000001";
    m_strStaffName = "";
    m_strStaffPassword = "";
    m_strSex = "未知";
    m_strBirthday = "0000-00-00";
    m_strDepartment = "未知";
    m_strJobName = "未知";
    m_fWage = 0.0;
    m_nWorkingAge = 0;
    m_strPlace = "未知";
    m_strEducation = "未知";
    m_strSpecialty = "未知",
    m_strAddress="未知";
    m_strEMail="未知";
    m_strPhone="未知",
    m_strEnterCampany = QDateTime::currentDateTime().toString();
    m_strLeaveCampany = "0000-00-00";
    m_strIntroduction="未知";
    m_strParam = "无";
}

void CStaffInfo::SetStaffID(const QString id)
{
    m_strStaffID = id;
}
void CStaffInfo::SetStaffName(const QString& name)
{
    m_strStaffName = name;
}
void CStaffInfo::SetStaffPassword(const QString& password)
{
    m_strStaffPassword = password;
}
void CStaffInfo::SetSex(const QString& sex)
{
    m_strSex = sex;
}
void CStaffInfo::SetBirthday(const QString& date)
{
    m_strBirthday = date;
}
void CStaffInfo::SetDepartment(const QString& department)
{
    m_strDepartment = department;
}
void CStaffInfo::SetJobName(const QString& jobname)
{
    m_strJobName = jobname;
}
void CStaffInfo::SetWage(const float wage)
{
    m_fWage = wage;
}
void CStaffInfo::SetWorkingAge(const int workingage)
{
    m_nWorkingAge = workingage;
}
void CStaffInfo::SetPlace(const QString& place)
{
    m_strPlace = place;
}
void CStaffInfo::SetEducation(const QString& education)
{
    m_strEducation = education;
}
void CStaffInfo::SetSpecialty(const QString& specialty)
{
    m_strSpecialty = specialty;
}
void CStaffInfo::SetAddress(const QString& address)
{
    m_strAddress = address;
}
void CStaffInfo::SetEmail(const QString& email)
{
    m_strEMail = email;
}
void CStaffInfo::SetPhone(const QString& phone)
{
    m_strPhone = phone;
}
void CStaffInfo::SetEnterCompany(const QString& date)
{
    m_strEnterCampany = date;
}
void CStaffInfo::SetLeaveCompany(const QString& date)
{
    m_strLeaveCampany = date;
}
void CStaffInfo::SetIntroduction(const QString& introduction)
{
    m_strIntroduction = introduction;
}

void CStaffInfo::SetParam(const QString& param)
{
    m_strParam = param;
}


QString CStaffInfo::GetStaffID()
{
    return  m_strStaffID;
}
QString CStaffInfo::GetStaffName()
{
    return  m_strStaffName;
}
QString CStaffInfo::GetStaffPassword()
{
    return  m_strStaffPassword;
}
QString CStaffInfo::GetSex()
{
    return m_strSex;
}
QString CStaffInfo::GetBirthday()
{
    return  m_strBirthday;
}
QString CStaffInfo::GetDepartment()
{
    return  m_strDepartment;
}
QString CStaffInfo::GetJobName()
{
    return  m_strJobName;
}
float CStaffInfo::GetWage()
{
    return  m_fWage;
}
int CStaffInfo::GetWorkingAge()
{
    return  m_nWorkingAge;
}
QString CStaffInfo::GetPlace()
{
    return  m_strPlace;
}
QString CStaffInfo::GetEducation()
{
    return  m_strEducation;
}
QString CStaffInfo::GetSpecialty()
{
    return  m_strSpecialty;
}
QString CStaffInfo::GetAddress()
{
    return  m_strAddress;
}
QString CStaffInfo::GetEmail()
{
    return  m_strEMail;
}
QString CStaffInfo::GetPhone()
{
    return  m_strPhone;
}
QString CStaffInfo::GetEnterCampany()
{
    return  m_strEnterCampany;
}
QString CStaffInfo::GetLeaveCampany()
{
    return  m_strLeaveCampany;
}
QString CStaffInfo::GetIntroduction()
{
    return  m_strIntroduction;
}
QString CStaffInfo::GetParam()
{
    return  m_strParam;
}
