#ifndef STAFFINFO_H
#define STAFFINFO_H

#include "singleton.h"
#include <QString>



class CStaffInfo
{
public:
    CStaffInfo();
    ~CStaffInfo();

    void SetStaffID(const QString id);
    void SetStaffName(const QString& name);
    void SetStaffPassword(const QString& password);
    void SetSex(const int sex);
    void SetBirthday(const QString& date);
    void SetDepartment(const QString& department);
    void SetJobName(const QString& jobname);
    void SetWage(const float wage);
    void SetWorkingAge(const int workingage);
    void SetPlace(const QString& place);
    void SetEducation(const QString& education);
    void SetSpecialty(const QString& specialty);
    void SetAddress(const QString& address);
    void SetEmail(const QString& email);
    void SetPhone(const QString& phone);
    void SetEnterCompany(const QString& date);
    void SetLeaveCompany(const QString& date);
    void SetIntroduction(const QString& introduction);
    void SetParam(const QString& param);


    QString GetStaffID();
    QString GetStaffName();
    QString GetStaffPassword();
    int GetSex();
    QString GetBirthday();
    QString GetDepartment();
    QString GetJobName();
    float GetWage();
    int GetWorkingAge();
    QString GetPlace();
    QString GetEducation();
    QString GetSpecialty();
    QString GetAddress();
    QString GetEmail();
    QString GetPhone();
    QString GetEnterCampany();
    QString GetLeaveCampany();
    QString GetIntroduction();
    int GetResignation();
    QString GetParam();

private:

    void InitParams();

    QString m_strStaffID;
    QString m_strStaffName, m_strStaffPassword;

    // 性别（0 未知，1 男，2 女）
    int m_nSex;
    QString m_strSex;

    QString m_strBirthday, m_strDepartment, m_strJobName;
    float m_fWage;
    int m_nWorkingAge;

    QString m_strPlace, m_strEducation, m_strSpecialty,
        m_strAddress, m_strEMail, m_strPhone,
        m_strEnterCampany, m_strLeaveCampany, m_strIntroduction;

    QString m_strParam;
};

typedef Singleton<CStaffInfo> StaffInfoSingleton;

#endif // STAFFINFO_H
