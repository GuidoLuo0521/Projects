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

    // ��Ȧ
    QMap<int, CShape*> m_mapApertures;

    // ��ǰ���õĹ�Ȧ
    int m_nCurrentAptr;

};

#endif // PARSERGERBER_H
