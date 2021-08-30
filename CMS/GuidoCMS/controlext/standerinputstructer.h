#ifndef STANDERINPUTSTRUCTER_H
#define STANDERINPUTSTRUCTER_H

#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>


class StanderInputStructer : public QObject
{
    Q_OBJECT
public:
    explicit StanderInputStructer(
            const QString& label,
            Qt::Orientation orient = Qt::Horizontal);

    virtual ~StanderInputStructer();

    Qt::Orientation Orient() const;

    QLabel * Label() const;
    QBoxLayout * Layout() const;

private:
    Qt::Orientation m_Orient;
protected:
    QLabel * m_pLabel;
    QBoxLayout * m_pMainLayout;
};

#endif // STANDERINPUTFORM_H
