#include "cparsergerber.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

CParserGerber::CParserGerber()
{

}

CParserGerber::~CParserGerber()
{
    qDeleteAll(m_mapApertures);
}

bool CParserGerber::Parser(const QString &strPath)
{
    if(QFile::exists(strPath) == false)
        return false;

    QFile file(strPath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString line;
        QTextStream in(&file);  //���ļ�������
        line = in.readLine();//��ȡһ�зŵ��ַ�����

        qDebug() << line;

        while(!line.isNull())//�ַ���������
        {
            line=in.readLine();//ѭ����ȡ����
            qDebug() << line;

        }
    }
    file.close();
}
