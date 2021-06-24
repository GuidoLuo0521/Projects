#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>

/*
 * �����ļ���Ϣ
*/

enum ConvertType
{
    CT_NONE,
    CT_ING,
    CT_OVER

};

/// �ļ���Ϣ
///
struct stFileInfo
{

    // ��ǰѡ��ľ���·��
    static QString s_strCurrentFolderPath ;

    stFileInfo(){}

    stFileInfo(QString strName, ConvertType ct) : strFileName(strName), convertType(ct) { }

    // �ļ���
    QString strFileName;

    // ת������
    ConvertType convertType;

    stFileInfo operator =(const stFileInfo& item)
    {
        this->strFileName = item.strFileName;
        this->convertType = item.convertType;

        return *this;
    }


};



#endif // FILEINFO_H
