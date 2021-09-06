#ifndef STANDERTEXTEDIT_H
#define STANDERTEXTEDIT_H

#include "controlext/standerinputstructer.h"
#include <QLabel>
#include <QPlainTextEdit>
#include <QTextEdit>

class StanderPlainTextEdit : public StanderInputStructer
{
    Q_OBJECT
public:
    StanderPlainTextEdit(
        const QString& label,
        const QString& text,
        const Qt::Orientation orient = Qt::Horizontal);

    QString Text() const;
    QPlainTextEdit * TextEdit() const;

private:
    QPlainTextEdit * m_pTextEdit;
};


class StanderRichTextEdit : public StanderInputStructer
{
    Q_OBJECT
public:
    StanderRichTextEdit(
        const QString& label,
        const QString& text,
        const Qt::Orientation orient = Qt::Horizontal);

    QString Text() const;
    QTextEdit * TextEdit() const;

private:
    QTextEdit * m_pTextEdit;
};

#endif // STANDERPLAINTEXTEDIT_H
