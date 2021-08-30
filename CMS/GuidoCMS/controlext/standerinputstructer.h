#ifndef STANDERINPUTSTRUCTER_H
#define STANDERINPUTSTRUCTER_H

#include <QHBoxLayout>
#include <QWidget>

class StanderInputStructer : public QObject
{
    Q_OBJECT
public:
    explicit StanderInputStructer(
        Qt::Orientation orient = Qt::Horizontal);

    virtual ~StanderInputStructer();

    Qt::Orientation Orient() const;
    QBoxLayout * Layout() const;

private:
    Qt::Orientation m_Orient;
protected:
    QBoxLayout * m_pMainLayout;

};

#endif // STANDERINPUTFORM_H
