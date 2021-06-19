#include "cpadsymbol.h"


CPadSymbol::CPadSymbol(const PadSymbolType pst, const QPoint &cpt, const int angle, const bool positive)
    : CSymbol(ST_PAD, positive)
    , m_PadSymbolType(pst)
    , m_ptCenter(cpt)
    , m_nAngle(angle)

{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRectPadSymbol::CRectPadSymbol(const QPoint &cpt, const int width, const int heigth, const int angle, const bool positive)
    : CPadSymbol(PST_RECTANGLE, cpt, angle, positive)
    , m_nWidth(width)
    , m_nHeight(heigth)
{

}

void CRectPadSymbol::Draw(QPainter &painter)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRoundPadSymbol::CRoundPadSymbol(const QPoint &cpt, const int rad, const int angle, const bool positive)
    : CPadSymbol(PST_ROUNT, cpt, angle, positive)
    , m_nRad(rad)
{

}

void CRoundPadSymbol::Draw(QPainter &painter)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSquarePadSymbol::CSquarePadSymbol(const QPoint &cpt, const int width, const int angle, const bool positive)
    : CPadSymbol(PST_SQUARE, cpt, angle, positive)
    , m_nWidth(width)
{

}

void CSquarePadSymbol::Draw(QPainter &painter)
{

}
