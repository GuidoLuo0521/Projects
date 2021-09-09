#ifndef ECGMARKDEF_H
#define ECGMARKDEF_H

#include <QString>
#include <QList>
#include <QDebug>

enum MarkPointType
{
    PS,
    P,
    PE,
    QS,
    R,
    SE,
    TS,
    T,
    TE,
    MARK_POINT_COUNT
};

struct HitMarkPoint
{
    int nSelectPos;
    int nNewPos;       // x 轴所在位置
    int nIndex;     // 数组中所在索引，-1 的时候为添加点
    MarkPointType type; // 类型

    HitMarkPoint(int spos = -1,int npos = -1, MarkPointType t = MARK_POINT_COUNT) :nSelectPos(spos), nNewPos(npos), nIndex(-1), type(t) { };

    void Clear(){ nSelectPos = -1 ; nNewPos = -1; nIndex = -1; type = MARK_POINT_COUNT; }

};

struct MarkPointStructure
{
    int nPos;
    QString strType;

    MarkPointStructure(const int nPos = 0,QString str = "X") : nPos(nPos), strType(str) {}

    //拷贝构造函数
    MarkPointStructure(const MarkPointStructure & p)
    {
        this->nPos = p.nPos;
        this->strType = p.strType;
    }

    static bool CompMarkPoint (const MarkPointStructure& a, const MarkPointStructure& b)
    {
        return a.nPos < b.nPos;
    }
};



// 和上面枚举对应
extern QStringList g_listMarkPointTypeNameInJson;
extern QStringList g_listMarkPointTypeName;

typedef QVector<MarkPointStructure> MarkPointVect;

typedef QVector<double> EcgDataVect;

typedef EcgDataVect CustomplotAxisData[2];


#endif // ECGMARKDEF_H
