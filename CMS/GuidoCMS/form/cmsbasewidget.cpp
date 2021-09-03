#include "cmsbasewidget.h"

CMSBaseWidget::CMSBaseWidget(QWidget *parent) : QWidget(parent)
{

}

CMSBaseWidget::~CMSBaseWidget()
{

}


void CMSBaseWidget::slotSetShow(bool bShow)
{
    this->setHidden(!bShow);
}
