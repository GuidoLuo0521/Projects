#ifndef CSHAPE_H
#define CSHAPE_H


#include <QRect>

enum ShapeType
{
    ST_RECT,
    ST_ROUND,
    ST_SQUARE
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CShape class
///
class CShape
{
public:
    CShape(ShapeType st) : m_ShapeType(st) {};
    virtual QRect GetBoundingRect() = 0;

protected:
    ShapeType m_ShapeType;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CRectShape class
///
class CRectShape : public CShape
{
public:
    CRectShape(const short width, const short heigth) : CShape(ST_RECT), m_nWidth(width), m_nHeight(heigth){}
    virtual QRect GetBoundingRect() { return QRect(-m_nWidth/2, m_nHeight/2, m_nWidth/2, m_nHeight/2); }

protected:
    short m_nWidth;
    short m_nHeight;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CRoundShape class
///
class CRoundShape : public CShape
{
public:
    CRoundShape(const short rad) : CShape(ST_ROUND), m_nRad(rad) {};
    ~CRoundShape(){}

    virtual QRect GetBoundingRect() { return QRect( -m_nRad/2, -m_nRad/2, m_nRad/2, m_nRad/2); }

protected:
    short m_nRad;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CSquareShape class
///
class CSquareShape : public CShape
{
public:
    CSquareShape(const short width) : CShape(ST_SQUARE), m_nWidth(width) {};
    virtual QRect GetBoundingRect() { return QRect(-m_nWidth/2, m_nWidth/2, m_nWidth/2, m_nWidth/2); }

protected:
    short m_nWidth;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CHollowRectInRect class
///
class CHollowRectInRectShape : public CRectShape
{
public:
    CHollowRectInRectShape(const short ow, const short oh, const short iw, const short ih) : CRectShape(ow, oh), m_nInnerWidth(iw), m_nInnerHeight(ih) {}
protected:
    short m_nInnerWidth;
    short m_nInnerHeight;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CHollowRoundInRect class
///
class CHollowRoundInRectShape : public CRectShape
{
public:
    CHollowRoundInRectShape(const short ow, const short oh, const short irad) : CRectShape(ow, oh), m_nInnerRad(irad) {}
protected:
    short m_nInnerRad;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CHollowRoundInRound class
///
class CHollowRoundInRoundShape : public CRoundShape
{
public:
    CHollowRoundInRoundShape(const short orad,  const short irad) : CRoundShape(orad), m_nInnerRad(irad) {}
protected:
    short m_nInnerRad;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief The CHollowRectInRound class
///
class CHollowRectInRoundShape : public CRoundShape
{
public:
    CHollowRectInRoundShape(const short orad, const short iw, const short ih) : CRoundShape(orad), m_nInnerWidth(iw), m_nInnerHeight(ih) {}
protected:
    short m_nInnerWidth;
    short m_nInnerHeight;
};


#endif // CSHAPE_H
