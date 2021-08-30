#include "standerdateedit.h"

#include <QHBoxLayout>

StanderDateEdit::StanderDateEdit(
        const QString &label,
        const QString &date,
        Qt::Orientation orient) :
    StanderInputStructer(label, orient),
    m_pDateEdit(nullptr)
{
    m_pDateEdit = new QDateEdit;
    m_pDateEdit->setCalendarPopup(true);
    m_pDateEdit->setDisplayFormat("yyyy-MM-dd");
    m_pDateEdit->setDate(QDate::fromString(date, Qt::ISODate));

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pDateEdit);
}

QString StanderDateEdit::Date(QString format)
{
    return m_pDateEdit->date().toString(format);
}

QDateEdit *StanderDateEdit::DateEdit() const
{
    return m_pDateEdit;
}
