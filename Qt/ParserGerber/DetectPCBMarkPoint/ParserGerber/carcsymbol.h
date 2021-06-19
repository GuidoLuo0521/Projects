#ifndef CARCSYMBOL_H
#define CARCSYMBOL_H

#include "csymbol.h"

class CArcSymbol : CSymbol
{
public:
    CArcSymbol(
            const QPoint& spt,
            const QPoint& ept,
            const QPoint& cpt,
            const short angle,
            const short width,
            const bool positive);

    virtual void Draw(QPainter& painter );


private:
    QPoint m_ptStart;
    QPoint m_ptEnd;
    QPoint m_ptCenter;
    short  m_nWidth;
    short  m_nAngle;
};

#endif // CARCSYMBOL_H
