#include "standerlineedit.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

StanderLineEdit::StanderLineEdit(
    const QString & label,
    const QString & lineedit,
    Qt::Orientation orient) :
    StanderInputStructer(orient)
{    
    if(orient == Qt::Vertical)
        m_pMainLayout = new QVBoxLayout;
    else
        m_pMainLayout = new QHBoxLayout;

    m_pLabel = new QLabel(label);
    m_pLineEdit = new QLineEdit(lineedit);

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pLineEdit);
}

QString StanderLineEdit::Text() const
{
    return  m_pLineEdit->text();
}

QLabel *StanderLineEdit::Label() const
{
    return m_pLabel;
}

QLineEdit *StanderLineEdit::LineEdit() const
{
    return m_pLineEdit;
}
