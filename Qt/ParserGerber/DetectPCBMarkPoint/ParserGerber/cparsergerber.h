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

    // ��ǰ���õĹ�Ȧ G54 ����
    int m_nCurrentAptr;

    // �ܹ���λ������ FS ����
    int m_nTotalNumSize;



};

#endif // PARSERGERBER_H
