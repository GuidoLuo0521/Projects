#ifndef CSYMBOL_H
#define CSYMBOL_H

#include <QPainter>


enum SymbolType
{
    ST_LINE = 0,
    ST_PAD,
    ST_ARC,
    ST_POLYGON
};

class CSymbol
{
public:
    CSymbol(const SymbolType st, const bool positive) : m_SymbolType(st), m_bPositive(positive) {}
    ~CSymbol() {}

    virtual void Draw(QPainter& painter ) = 0;

protected:
    SymbolType m_SymbolType;    // 图像类型
    bool m_bPositive;           // 正负性

};

#endif // CSYMBOL_H
