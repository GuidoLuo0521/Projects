#include "standertextedit.h"

#include <QHBoxLayout>

StanderPlainTextEdit::StanderPlainTextEdit(
    const QString &label,
    const QString &text,
    const Qt::Orientation orient) :
    StanderInputStructer(label, orient),
    m_pTextEdit(nullptr)
{
    m_pTextEdit = new QPlainTextEdit(text);

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pTextEdit);
}

QString StanderPlainTextEdit::Text() const
{
    return  m_pTextEdit->toPlainText();
}

QPlainTextEdit *StanderPlainTextEdit::TextEdit() const
{
    return  m_pTextEdit;
}

////////////////////////////////////////////////////////////////////////
StanderRichTextEdit::StanderRichTextEdit(
    const QString &label,
    const QString &text,
    const Qt::Orientation orient) :
    StanderInputStructer(label, orient),
    m_pTextEdit(nullptr)
{
    m_pTextEdit = new QTextEdit(text);

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pTextEdit);
}

QString StanderRichTextEdit::Text() const
{
    return  m_pTextEdit->toHtml();
}

QTextEdit *StanderRichTextEdit::TextEdit() const
{
    return  m_pTextEdit;
}
