#include "cpadsymbol.h"
#include "commontool.h"

CPadSymbol::CPadSymbol(const PadSymbolType pst, const QPoint &cpt, const int angle, const bool positive)
    : CSymbol(ST_PAD, positive)
    , m_ptCenter(cpt)
    , m_nAngle(angle)
    , m_PadSymbolType(pst)

{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRectPadSymbol::CRectPadSymbol(const QPoint &cpt, const short width, const short heigth, const short angle, const bool positive)
    : CPadSymbol(PST_RECTANGLE, cpt, angle, positive)
    , CRectShape(width, heigth)
{

}

void CRectPadSymbol::Draw(QPainter &painter)
{

}

QRect CRectPadSymbol::GetBoundingRect()
{
    QRect rect = CRectShape::GetBoundingRect();
    rect = CommonMathTool::RotateRect(rect, m_nAngle);
    rect.moveCenter(m_ptCenter);

    return rect;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRoundPadSymbol::CRoundPadSymbol(const QPoint &cpt, const short rad, const short angle, const bool positive)
    : CPadSymbol(PST_ROUNT, cpt, angle, positive)
    , CRoundShape(rad)
{

}

void CRoundPadSymbol::Draw(QPainter &painter)
{

}

QRect CRoundPadSymbol::GetBoundingRect()
{
    QRect rect = CRoundShape::GetBoundingRect();
    //rect = CommonMathTool::RotateRect(rect, m_nAngle);
    rect.moveCenter(m_ptCenter);

    return rect;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSquarePadSymbol::CSquarePadSymbol(const QPoint &cpt, const short width, const short angle, const bool positive)
    : CPadSymbol(PST_SQUARE, cpt, angle, positive)
    , CSquareShape(width)
{

}

void CSquarePadSymbol::Draw(QPainter &painter)
{

}

QRect CSquarePadSymbol::GetBoundingRect()
{
    QRect rect = CSquareShape::GetBoundingRect();
    rect = CommonMathTool::RotateRect(rect, m_nAngle);
    rect.moveCenter(m_ptCenter);

    return rect;
}
