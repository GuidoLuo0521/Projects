#ifndef STANDERRANGEEDIT_H
#define STANDERRANGEEDIT_H

#include "standerinputstructer.h"
#include <QSpinBox>

class StanderRangeEdit : public StanderInputStructer
{
    Q_OBJECT
public:
    StanderRangeEdit(
        const QString& label,
        const double lower,
        const double higher,
        Qt::Orientation orient);

    double Lower();
    double Higher();

private:
    QDoubleSpinBox * m_pSpinBoxLower;
    QDoubleSpinBox * m_pSpinBoxHigher;
};

#endif // STANDERRANGEEDIT_H
