#include "standercombobox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

StanderComboBox::StanderComboBox(const QString &label,
    const QStringList &items,
    Qt::Orientation orient) :
    StanderInputStructer(label, orient),
    m_pCombobox(nullptr)
{
    m_pCombobox = new QComboBox;
    for( int i = 0; i < items.size(); ++i)
        m_pCombobox->insertItem(i, items[i]);

    m_pMainLayout->addWidget(m_pLabel);
    m_pMainLayout->addWidget(m_pCombobox);

    m_pMainLayout->setStretch(0, 1);
    m_pMainLayout->setStretch(1, 9);
}

StanderComboBox::~StanderComboBox()
{

}

QString StanderComboBox::CurrentText() const
{
    return  m_pCombobox->currentText();
}

QComboBox *StanderComboBox::ComboBox() const
{
    return m_pCombobox;
}
