#ifndef STANDERCOMBOBOX_H
#define STANDERCOMBOBOX_H

#include "controlext/standerinputstructer.h"
#include <QLabel>
#include <QComboBox>

class StanderComboBox : public StanderInputStructer
{
    Q_OBJECT

public:
    explicit StanderComboBox(
        const QString& label,
        const QStringList& items,
        Qt::Orientation orient = Qt::Horizontal);

    ~StanderComboBox();

    QString CurrentText() const;
    QComboBox * ComboBox() const;

private:
    QLabel * m_pLabel;
    QComboBox * m_pCombobox;
};

#endif // STANDERCOMBOBOXINPUTFORM_H
