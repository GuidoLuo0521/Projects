#ifndef CMSDATEBASEDEF_H
#define CMSDATEBASEDEF_H

#include <QString>

struct CMSDB_Filed_Table_Staff
{
    static const QString strTableName;
    static const QString strStaffID;
    static const QString strStaffName;
    static const QString strStaffPassword;
    static const QString strSex;
    static const QString strBirthday;
    static const QString strDepartment;
    static const QString strJobName;
    static const QString strWage;
    static const QString strWorkingAge;
    static const QString strPlace;
    static const QString strEducation;
    static const QString strSpecialty;
    static const QString strAddress;
    static const QString strEmail;
    static const QString strPhone;
    static const QString strEnterCompany;
    static const QString strLeaveCompany;
    static const QString strIntroduction;
    static const QString strParams;
};

struct CMSDB_Filed_Table_Department {

    static const QString strTableName ;
    static const QString strDepartmntID ;
    static const QString strDepartmentName ;
    static const QString strDescription ;
    static const QString strParam ;

};

struct CMSDB_Filed_Table_Job {

    static const QString strTableName;
    static const QString strJobID ;
    static const QString strJobName ;
    static const QString strBasicWage ;
    static const QString strDescription ;
    static const QString strParam ;

};

struct CMSDB_Filed_Table_Permission {

    static const QString strTableName;
    static const QString strPermissionID ;
    static const QString strPermissionName ;
    static const QString strParam ;

};

struct CMSDB_Filed_Table_Role {

    static const QString strTableName;
    static const QString strRoleID ;
    static const QString strRoleName ;
    static const QString strDescription ;
    static const QString strParam ;

};

struct CMSDB_Filed_Table_RolePermission {

    static const QString strTableName;
    static const QString strRoleID ;
    static const QString strPermissionID ;
    static const QString strDescription ;
    static const QString strParam ;

};

struct CMSDB_Filed_Table_StaffRole {

    static const QString strTableName;
    static const QString strRoleID ;
    static const QString strStaffID ;
    static const QString strParam ;

};




#endif // CMSDATEBASEDEF_H
