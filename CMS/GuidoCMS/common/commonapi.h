#ifndef COMMONAPI_H
#define COMMONAPI_H

#include "database/cmsdatabase.h"
#include "staffinfo.h"

/**********************************************************************/
// 初始化
void InitGlobalParams();

// 初始化数据库连接
void LoadDatabaseSingleton();

// 初始化当前账户
void CreateCurrentStaffInfoSingleton();

/**********************************************************************/
CStaffInfo* GetStaffInfo(const QString& strStaffID, const QString& strStaffPassWord);


/**********************************************************************/
QString GetIPPath();
QString GetMacPath();

#endif // COMMONAPI_H
