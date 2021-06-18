#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>

/*
 * 定义文件信息
*/

struct stFileInfo
{

    // 当前选择的绝对路径
    static QString s_strCurrentFolderPath ;

    stFileInfo(QString strName, bool bCveted) : strFileName(strName), bIsConverted(bCveted) { }

    // 文件名
    QString strFileName;

    // 是否已经转换完成
    bool bIsConverted = false;


};



#endif // FILEINFO_H
