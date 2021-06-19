#include "clinesymbol.h"


CLineSymbol::CLineSymbol(const QPoint spt, const QPoint ept, const short width, const bool positive)
    : CSymbol( ST_LINE, positive)
    , m_ptStart(spt)
    , m_ptEnd(ept)
    , m_nWidth(width)
{

}

void CLineSymbol::Draw(QPainter &painter)
{

}
