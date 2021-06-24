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

    bool ParserFS(const QString& line);
    bool ParserMO(const QString& line);
    bool ParserLP(const QString& line);
    bool ParserG54(const QString& line);

    bool ParserAD(const QString& line);
    bool ParserAD_C(const QString& line);
    bool ParserAD_R(const QString& line);

    bool ParserPoint(const QString& line);

protected:

    QMap<int, CShape*> m_mapApertures;

    // 当前采用的光圈 G54 决定
    int m_nCurrentAptr;

    // 总共的位数，由 FS 决定
    int m_nTotalNumSize;



};

#endif // PARSERGERBER_H
