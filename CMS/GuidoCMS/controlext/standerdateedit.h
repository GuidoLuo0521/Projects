#ifndef STANDERDATEEDIT_H
#define STANDERDATEEDIT_H

#include "controlext/standerinputstructer.h"
#include <QLabel>
#include <QDateEdit>

class StanderDateEdit : public StanderInputStructer
{
    Q_OBJECT
public:
    StanderDateEdit(
        const QString& label,
        const QString& date,
        Qt::Orientation orient = Qt::Horizontal);

    QString Date(QString format = "yyyy-MM-dd");

    QDateEdit* DateEdit () const;
private:
    QDateEdit * m_pDateEdit;

};

#endif // STANDERDATEEDIT_H
