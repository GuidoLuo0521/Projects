#ifndef PARSERGERBER_H
#define PARSERGERBER_H

#include <QString>
#include <QMap>
#include "CShape.h"

class CParserGerber
{
public:
    CParserGerber();
    ~CParserGerber();

public:
    bool Parser(const QString& strPath);

    bool ParserAD();
    bool ParserAD_C();
    bool ParserAD_R();


protected:

    // 光圈
    QMap<int, CShape*> m_mapApertures;

    // 当前采用的光圈
    int m_nCurrentAptr;

};

#endif // PARSERGERBER_H
