#include "standerplaintextedit.h"

#include <QHBoxLayout>

StanderPlainTextEdit::StanderPlainTextEdit(
    const QString &label,
    const QString &plaintext,
    const Qt::Orientation orient) :
    StanderInputStructer(orient),
    m_pLabel(nullptr),
    m_pPlainTextEdit(nullptr)
{
    if(orient == Qt::Vertical)
        m_pMainLayout = new QVBoxLayout;
    else
        m_pMainLayout = new QHBoxLayout;

    m_pLabel = new QLabel(label);
    m_pPlainTextEdit = new QPlainTextEdit(plaintext);

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pPlainTextEdit);
}

QString StanderPlainTextEdit::PlainText() const
{
    return  m_pPlainTextEdit->toPlainText();
}

QLabel *StanderPlainTextEdit::Label() const
{
    return  m_pLabel;
}

QPlainTextEdit *StanderPlainTextEdit::PlainTextEdit() const
{
    return  m_pPlainTextEdit;
}
