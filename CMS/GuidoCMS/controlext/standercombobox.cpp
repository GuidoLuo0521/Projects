#include "standercombobox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

StanderComboBox::StanderComboBox(const QString &label,
    const QStringList &items,
    Qt::Orientation orient) :
    StanderInputStructer(orient),
    m_pLabel(nullptr),
    m_pCombobox(nullptr)
{
    m_pLabel = new QLabel(label);
    m_pCombobox = new QComboBox;
    for( int i = 0; i < items.size(); ++i)
        m_pCombobox->insertItem(i, items[i]);

    if(orient == Qt::Vertical)
        m_pMainLayout = new QVBoxLayout;
    else
        m_pMainLayout = new QHBoxLayout;

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
