#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QPoint>
#include <QRect>

/*
namespace Common {

}
*/

class CommonFileTool
{
public:
    CommonFileTool();

    static QString GetSelectFolder();

    static QString GetSelectFile();

};


class CommonMathTool
{

public:
    static const double PI;

    /*
     * 以(x0,y0)为旋转中心点，
     * 已经知旋转前点的位置(x1,y1)和旋转的角度a，求旋转后点的新位置(x2,y2)
     *
     * 如果是逆时针旋转：
     * x2 = (x1 - x0) * cosa - (y1 - y0) * sina + x0
     * y2 = (y1 - y0) * cosa + (x1 - x0) * sina + y0
     * 如果是顺时针旋转：
     * x2 = (x1 - x0) * cosa + (y1 - y0) * sina + x0
     * y2 = (y1 - y0) * cosa - (x1 - x0) * sina + y0
    */

    static QPoint RotatePoint(const QPoint& rpt, const short angle);
    static QPoint RotatePoint(const QPoint& cpt, const QPoint& rpt, const short angle);

    static QRect RotateRect(const QRect& rect, const short angle);
    static QRect RotateRect(const QPoint& cpt, const QRect& rect, const short angle);

};


#endif // COMMON_H
