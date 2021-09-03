#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMutex>
#include "common/controlinclude.h"
#include "systemmanagerdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotExitLogin();
    void slotShowWindow();
    void slotUpdateTime();
    void slotShowCurrentAccount();
    void slotUpdateStaffPassword();

signals:
    void signalExitCurrentAccount();

private:
    void InitLayout();

    QWidget * InitMenuBar();
    QWidget * InitToolBar();

    QWidget * InitStatuBar();

    QLabel * m_pStatuTimeLabel;
    QLabel * m_pStatuAccountLabel;

    QAction * m_pActionExit;
    QAction * m_pActionUPW;

    QStackedWidget * m_pStackCentralWidget;
    SystemManagerDialog * m_pSystemManagerDialog;

};

#endif // MAINWINDOW_H
