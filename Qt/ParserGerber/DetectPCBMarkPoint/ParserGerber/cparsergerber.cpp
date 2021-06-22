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
    QString str;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            str = file.readLine();

            if(str.count() < 2 || str[0] == '#')
                continue;

                 if(str.startsWith("%FS"))  ParserFS(str.mid(1));
            else if(str.startsWith("%MO"))  ParserMO(str.mid(1));
            else if(str.startsWith("%AD"))  ParserAD(str.mid(1));
            else if(str.startsWith("%LP"))  ParserLP(str.mid(1));
            else if(str.startsWith("%G54")) ParserG54(str);
            else if(str.startsWith("X") || str.startsWith("Y")) ParserG54(str);

        }
        file.close();

    }
}

bool CParserGerber::ParserFS(const QString &line)
{

}

bool CParserGerber::ParserMO(const QString &line)
{
    // %MOIN*%


}

bool CParserGerber::ParserLP(const QString &line)
{
    // %LPD*%

}

bool CParserGerber::ParserG54(const QString &line)
{

}

bool CParserGerber::ParserAD(const QString &line)
{

}
