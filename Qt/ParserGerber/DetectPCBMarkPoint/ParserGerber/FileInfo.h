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

    stFileInfo(QString strName, bool bCveted) : strFileName(strName), bIsConverted(bCveted) { }

    // �ļ���
    QString strFileName;

    // �Ƿ��Ѿ�ת�����
    bool bIsConverted = false;


};



#endif // FILEINFO_H
