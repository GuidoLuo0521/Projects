#ifndef CLINESYMBOL_H
#define CLINESYMBOL_H

#include "csymbol.h"

class CLineSymbol : CSymbol
{
public:

    CLineSymbol(const QPoint spt,
                const QPoint ept,
                const short width,
                const bool positive);

    virtual void Draw(QPainter& painter);

protected:
    QPoint m_ptStart;
    QPoint m_ptEnd;
    short m_nWidth;
    bool  m_bRoundHat;
};

#endif // CLINESYMBOL_H
