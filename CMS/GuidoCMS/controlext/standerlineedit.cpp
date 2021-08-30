#include "standerlineedit.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

StanderLineEdit::StanderLineEdit(
    const QString & label,
    const QString & lineedit,
    Qt::Orientation orient) :
    StanderInputStructer(label, orient)
{    
    m_pLineEdit = new QLineEdit(lineedit);

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pLineEdit);
}

QString StanderLineEdit::Text() const
{
    return  m_pLineEdit->text();
}

QLineEdit *StanderLineEdit::LineEdit() const
{
    return m_pLineEdit;
}
