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
        QTextStream in(&file);  //用文件构造流
        line = in.readLine();//读取一行放到字符串里

        qDebug() << line;

        while(!line.isNull())//字符串有内容
        {
            line=in.readLine();//循环读取下行
            qDebug() << line;

        }
    }
    file.close();
}
