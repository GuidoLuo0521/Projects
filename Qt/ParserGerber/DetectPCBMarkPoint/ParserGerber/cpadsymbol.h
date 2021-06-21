#ifndef CPADSYMBOL_H
#define CPADSYMBOL_H

#include "csymbol.h"
#include "CShape.h"

enum PadSymbolType
{
    PST_ROUNT = 0,
    PST_SQUARE = 0,
    PST_RECTANGLE
};


/////////////////////////////////////////////////////////////////////////////////////
/// \brief The CPadSymbol class
///
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

/////////////////////////////////////////////////////////////////////////////////////
/// \brief The CSquarePadSymbol class
///
class CSquarePadSymbol : public CPadSymbol, CSquareShape
{
public:
    CSquarePadSymbol(const QPoint& cpt, const short width, const short angle, const bool positive);
    ~CSquarePadSymbol(){}

    virtual void Draw(QPainter& painter) override;
    virtual QRect GetBoundingRect() override;
};

/////////////////////////////////////////////////////////////////////////////////////
/// \brief The CRectPadSymbol class
///
class CRectPadSymbol : public CPadSymbol, CRectShape
{
public:
    CRectPadSymbol(const QPoint& cpt, const short width, const short heigth, const short angle, const bool positive);
    ~CRectPadSymbol(){}

    virtual void Draw(QPainter& painter) override;
    virtual QRect GetBoundingRect() override;

};

/////////////////////////////////////////////////////////////////////////////////////
/// \brief The CRoundPadSymbol class
///
class CRoundPadSymbol : public CPadSymbol, CRoundShape
{
public:
    CRoundPadSymbol(const QPoint& cpt, const short rad, const short angle, const bool positive);
    ~CRoundPadSymbol(){}

    virtual void Draw(QPainter& painter) override;
    virtual QRect GetBoundingRect() override;
};


#endif // CPADSYMBOL_H
