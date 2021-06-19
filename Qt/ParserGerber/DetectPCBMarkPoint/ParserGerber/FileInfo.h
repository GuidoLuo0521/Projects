#ifndef FILEINFO_H
#define FILEINFO_H

#include <QString>

/*
 * �����ļ���Ϣ
*/

struct stFileInfo
{

    // ��ǰѡ��ľ���·��
    static QString s_strCurrentFolderPath ;

    stFileInfo(){}

    stFileInfo(QString strName, bool bCveted) : strFileName(strName), bIsConverted(bCveted) { }

    // �ļ���
    QString strFileName;

    // �Ƿ��Ѿ�ת�����
    bool bIsConverted = false;

    stFileInfo operator =(const stFileInfo& item)
    {
        this->strFileName = item.strFileName;
        this->bIsConverted = item.bIsConverted;

        return *this;
    }


};



#endif // FILEINFO_H
