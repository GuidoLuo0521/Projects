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

    stFileInfo(){}

    stFileInfo(QString strName, bool bCveted) : strFileName(strName), bIsConverted(bCveted) { }

    // 文件名
    QString strFileName;

    // 是否已经转换完成
    bool bIsConverted = false;

    stFileInfo operator =(const stFileInfo& item)
    {
        this->strFileName = item.strFileName;
        this->bIsConverted = item.bIsConverted;

        return *this;
    }


};



#endif // FILEINFO_H
