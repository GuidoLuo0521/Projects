#ifndef STANDERLINEEDIT_H
#define STANDERLINEEDIT_H

#include "controlext/standerinputstructer.h"
#include <QLabel>
#include <QLineEdit>

class StanderLineEdit : public StanderInputStructer
{
    Q_OBJECT

public:
    StanderLineEdit(
        const QString& label,
        const QString& lineedit,
        Qt::Orientation orient = Qt::Horizontal);

    QString Text() const;
    QLineEdit * LineEdit() const;

private:
    QLineEdit * m_pLineEdit;
};

#endif // STANDERLINEEDIT_H
