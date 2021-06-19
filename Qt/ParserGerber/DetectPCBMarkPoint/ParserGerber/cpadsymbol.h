#ifndef CPADSYMBOL_H
#define CPADSYMBOL_H

#include "csymbol.h"

enum PadSymbolType
{
    PST_ROUNT = 0,
    PST_SQUARE = 0,
    PST_RECTANGLE
};

class CPadSymbol : CSymbol
{
public:
    CPadSymbol(const PadSymbolType pst, const QPoint& cpt, const int angle, const bool positive);
    ~CPadSymbol(){}

    virtual void Draw(QPainter& painter) = 0;

protected:
    QPoint m_ptCenter;
    short m_nAngle;
    PadSymbolType m_PadSymbolType;
};

class CSquarePadSymbol : CPadSymbol
{
public:
    CSquarePadSymbol(const QPoint& cpt, const int width, const int angle, const bool positive);
    ~CSquarePadSymbol(){}

    virtual void Draw(QPainter& painter);

protected:
    short m_nWidth;

};

class CRectPadSymbol : CPadSymbol
{
public:
    CRectPadSymbol(const QPoint& cpt, const int width, const int heigth, const int angle, const bool positive);
    ~CRectPadSymbol(){}

    virtual void Draw(QPainter& painter);

protected:
    short m_nWidth;
    short m_nHeight;
};

class CRoundPadSymbol : CPadSymbol
{
public:
    CRoundPadSymbol(const QPoint& cpt, const int rad, const int angle, const bool positive);
    ~CRoundPadSymbol(){}

    virtual void Draw(QPainter& painter);

protected:
    short m_nRad;
};


#endif // CPADSYMBOL_H
