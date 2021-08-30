#include "standerinputstructer.h"

StanderInputStructer::StanderInputStructer(const QString &label, Qt::Orientation orient) :
    m_Orient(orient),
    m_pLabel(nullptr),
    m_pMainLayout(nullptr)
{
    if(m_Orient == Qt::Vertical)
        m_pMainLayout = new QVBoxLayout;
    else
        m_pMainLayout = new QHBoxLayout;

    m_pLabel = new QLabel(label);
}

StanderInputStructer::~StanderInputStructer()
{

}

Qt::Orientation StanderInputStructer::Orient() const
{
    return m_Orient;
}

QLabel *StanderInputStructer::Label() const
{
    return m_pLabel;
}

QBoxLayout *StanderInputStructer::Layout() const
{
    return m_pMainLayout;
}
