#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>

/*
 * 定义文件信息
*/

enum ConvertType
{
    CT_NONE,
    CT_ING,
    CT_OVER

};

/// 文件信息
///
struct stFileInfo
{

    // 当前选择的绝对路径
    static QString s_strCurrentFolderPath ;

    stFileInfo(){}

    stFileInfo(QString strName, ConvertType ct) : strFileName(strName), convertType(ct) { }

    // 文件名
    QString strFileName;

    // 转换类型
    ConvertType convertType;

    stFileInfo operator =(const stFileInfo& item)
    {
        this->strFileName = item.strFileName;
        this->convertType = item.convertType;

        return *this;
    }


};



#endif // FILEINFO_H
