#include "standerinputstructer.h"

StanderInputStructer::StanderInputStructer(Qt::Orientation orient) :
    m_Orient(orient),
    m_pMainLayout(nullptr)
{
}

StanderInputStructer::~StanderInputStructer()
{

}

Qt::Orientation StanderInputStructer::Orient() const
{
    return m_Orient;
}

QBoxLayout *StanderInputStructer::Layout() const
{
    return m_pMainLayout;
}
