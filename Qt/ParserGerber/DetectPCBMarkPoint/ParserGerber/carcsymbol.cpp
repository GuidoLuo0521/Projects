#include "carcsymbol.h"

CArcSymbol::CArcSymbol(const QPoint &spt  , const QPoint &ept, const QPoint &cpt, const short angle, const short width, const bool positive)
    : CSymbol(ST_ARC, positive)
    , m_ptStart(spt)
    , m_ptEnd(ept)
    , m_ptCenter(cpt)
    , m_nWidth(width)
    , m_nAngle(angle)
{

}

void CArcSymbol::Draw(QPainter &painter)
{


}
