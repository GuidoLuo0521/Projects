#include "commontool.h"

#include <QFileDialog>
#include <complex>

const double CommonMathTool::PI = 3.14159265;


CommonFileTool::CommonFileTool()
{

}

QString CommonFileTool::GetSelectFolder()
{
    return QFileDialog::getExistingDirectory( nullptr, "select folder");
}

QString CommonFileTool::GetSelectFile()
{
    return QFileDialog::getOpenFileName( nullptr, "select file");
}

QPoint CommonMathTool::RotatePoint(const QPoint &rpt, const short angle)
{
    return RotatePoint(QPoint(), rpt, angle);
}

QPoint CommonMathTool::RotatePoint(const QPoint &cpt, const QPoint &rpt, const short angle)
{
    // x2 = (x1 - x0) * cosa + (y1 - y0) * sina + x0
    // y2 = (y1 - y0) * cosa - (x1 - x0) * sina + y0

    QPoint pt2 = rpt;

    double _arc = angle * PI / 180.0;
    double _sin = sin(_arc);
    double _cos = cos(_arc);
    double x1 = rpt.x(), y1 = rpt.y(), x0 = cpt.x(), y0 = cpt.y();

    pt2.setX( (x1 - x0) * _cos + (y1 - y0) * _sin + x0 );
    pt2.setY( (y1 - y0) * _cos - (x1 - x0) * _sin + y0 );

    return pt2;
}

QRect CommonMathTool::RotateRect(const QRect &rect, const short angle)
{
    return RotateRect(QPoint(), rect, angle);
}

QRect CommonMathTool::RotateRect(const QPoint &cpt, const QRect &rect, const short angle)
{
    QRect rect1 = rect;

    QPoint tl = RotatePoint(cpt, rect.topLeft(), angle);
    QPoint tr = RotatePoint(cpt, rect.topRight(), angle);
    QPoint bl = RotatePoint(cpt, rect.bottomLeft(), angle);
    QPoint br = RotatePoint(cpt, rect.bottomRight(), angle);

    int rx = qMax<int>(qMax<int>(qMax<int>(tl.x(), tr.x()), bl.x()),br.x());
    int lx = qMin<int>(qMin<int>(qMin<int>(tl.x(), tr.x()), bl.x()),br.x());
    int ty = qMax<int>(qMax<int>(qMax<int>(tl.y(), tr.y()), bl.y()),br.y());
    int by = qMin<int>(qMin<int>(qMin<int>(tl.y(), tr.y()), bl.y()),br.y());

    rect1.setTopLeft(QPoint(lx, ty));
    rect1.setBottomRight(QPoint(rx, by));

    return rect1;
}
