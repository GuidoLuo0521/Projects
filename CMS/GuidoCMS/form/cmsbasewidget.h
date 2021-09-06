#ifndef CMSBASEWIDGET_H
#define CMSBASEWIDGET_H

#include <QWidget>

class CMSBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMSBaseWidget(QWidget *parent = nullptr);
    virtual ~CMSBaseWidget();

public slots:
    void slotSetShow(bool bShow);

signals:


protected:
    virtual void InitLayout() = 0;

};

#endif // CMSBASEWIDGET_H
