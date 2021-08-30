#include "standerplaintextedit.h"

#include <QHBoxLayout>

StanderPlainTextEdit::StanderPlainTextEdit(
    const QString &label,
    const QString &plaintext,
    const Qt::Orientation orient) :
    StanderInputStructer(label, orient),
    m_pPlainTextEdit(nullptr)
{
    m_pPlainTextEdit = new QPlainTextEdit(plaintext);

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pPlainTextEdit);
}

QString StanderPlainTextEdit::PlainText() const
{
    return  m_pPlainTextEdit->toPlainText();
}

QPlainTextEdit *StanderPlainTextEdit::PlainTextEdit() const
{
    return  m_pPlainTextEdit;
}
