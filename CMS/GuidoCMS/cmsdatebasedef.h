#ifndef CMSDATEBASEDEF_H
#define CMSDATEBASEDEF_H

#include <QString>
#include <QStringList>

enum CMSDB_Table_Filed_Staff
{
    Staff_StaffID,
    Staff_StaffName,
    Staff_StaffPassword,
    Staff_Sex,
    Staff_Birthday,
    Staff_Department,
    Staff_JobName,
    Staff_Wage,
    Staff_WorkingAge,
    Staff_Place,
    Staff_Education,
    Staff_Specialty,
    Staff_Address,
    Staff_Email,
    Staff_Phone,
    Staff_EnterCompany,
    Staff_LeaveCompany,
    Staff_Introduction,
    Staff_Param,
    Staff_StaffTableName
};
extern const QStringList g_listCMSDB_Table_Filed_Staff;


enum CMSDB_Table_Filed_Department
{
    Department_DepartmntID ,
    Department_DepartmentName ,
    Department_State ,
    Department_Description ,
    Department_Param,
    Department_DepartmentTableName
};
extern const QStringList g_listCMSDB_Table_Filed_Department;


enum CMSDB_Table_Filed_Job
{
    Job_JobID ,
    Job_JobName ,
    Job_State,
    Job_BasicWage ,
    Job_Description ,
    Job_Param ,
    Job_JobTableName
};
extern const QStringList g_listCMSDB_Table_Filed_Job;


enum CMSDB_Table_Filed_Permission
{
    Permission_PermissionID ,
    Permission_PermissionName ,
    Permission_Param ,
    Permission_TableName
};
extern const QStringList g_listCMSDB_Table_Filed_Permission;


enum CMSDB_Table_Filed_Role
{
    Role_RoleID ,
    Role_RoleName ,
    Role_Description ,
    Role_Param,
    Role_TableName
};
extern const QStringList g_listCMSDB_Table_Filed_Role;


enum CMSDB_Table_Filed_RolePermission
{
    RolePermission_RoleID ,
    RolePermission_PermissionID ,
    RolePermission_Description ,
    RolePermission_Param,
    RolePermission_TableName
};
extern const QStringList g_listCMSDB_Table_Filed_RolePermission;


enum CMSDB_Table_Filed_StaffRole
{
    StaffRole_RoleID ,
    StaffRole_StaffID ,
    StaffRole_Param,
    StaffRole_TableName
};
extern const QStringList g_listCMSDB_Table_Filed_StaffRole;


/////////////////////////////////////////////////////////////////////

extern const QStringList g_strListDepartment;
extern const QStringList g_strListPlace;
extern const QStringList g_strListEducation;
extern const QStringList g_strListSpecialty;


#endif // CMSDATEBASEDEF_H
