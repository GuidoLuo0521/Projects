#ifndef CMSBASEWIDGET_H
#define CMSBASEWIDGET_H

#include <QWidget>

class CMSBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMSBaseWidget(QWidget *parent = nullptr);
    ~CMSBaseWidget();

public slots:
    void slotSetShow(bool bShow);

signals:

};

#endif // CMSBASEWIDGET_H
