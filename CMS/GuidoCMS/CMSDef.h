#ifndef CMSDEF_H
#define CMSDEF_H

#include "cmsdatabase.h"


extern const QString gk_strWebDBType;
extern const QString gk_strWebDBConnectionName;
extern const QString gk_strWebDBHostName;
extern const QString gk_strWebDBDatabaseName;
extern const QString gk_strWebDBUserName;
extern const QString gk_strWebDBPassword;
typedef Singleton<CMSDatabase> WebDatabaseSingleton;


extern const QString gk_strLocalDBType;
extern const QString gk_strLocalDBConnectionName;
extern const QString gk_strLocalDBHostName;
extern const QString gk_strLocalDBDatabaseName;
extern const QString gk_strLocalDBUserName;
extern const QString gk_strLocalDBPassword;
typedef Singleton<CMSDatabase> LocalDatabaseSingleton;



#endif // CMSDEF_H
