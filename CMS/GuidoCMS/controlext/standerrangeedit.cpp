#include "standerrangeedit.h"


StanderRangeEdit::StanderRangeEdit(
    const QString &label,
    const double lower,
    const double higher,
    Qt::Orientation orient) :
    StanderInputStructer(label, orient)
{
    m_pSpinBoxLower = new QDoubleSpinBox;
    m_pSpinBoxHigher = new QDoubleSpinBox;

    m_pSpinBoxLower->setValue(lower);
    m_pSpinBoxLower->setValue(higher);

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pSpinBoxLower);
    m_pMainLayout->addWidget(new QLabel("~"));
    m_pMainLayout->addWidget(m_pSpinBoxHigher);
}

double StanderRangeEdit::Lower()
{
    return m_pSpinBoxLower->value();
}

double StanderRangeEdit::Higher()
{
    return m_pSpinBoxHigher->value();
}
