#ifndef STANDERPLAINTEXTEDIT_H
#define STANDERPLAINTEXTEDIT_H

#include "controlext/standerinputstructer.h"
#include <QLabel>
#include <QPlainTextEdit>

class StanderPlainTextEdit : public StanderInputStructer
{
    Q_OBJECT
public:
    StanderPlainTextEdit(
        const QString& label,
        const QString& plaintext,
        const Qt::Orientation orient = Qt::Horizontal);

    QString PlainText() const;

    QLabel * Label() const;
    QPlainTextEdit * PlainTextEdit() const;

private:
    QLabel * m_pLabel;
    QPlainTextEdit * m_pPlainTextEdit;
};

#endif // STANDERPLAINTEXTEDIT_H
