#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMutex>
#include "systemmanagerdialog.h"
#include "weeklyreportdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum MainWindowDialogType
    {
        SystemManagerDialogType,
        WeeklyReportDialogType
    };

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotExitLogin();
    void slotShowWindow();
    void slotUpdateTime();
    void slotShowCurrentAccount();
    void slotUpdateStaffPassword();

    void slotShowDialog(MainWindow::MainWindowDialogType);
    void slotToolbarActionClicked();

signals:
    void signalExitCurrentAccount();
    void signalShowCurrentDialog(MainWindow::MainWindowDialogType);

private:    
    void InitLayout();

    QWidget * InitMenuBar();
    QWidget * InitToolBar();
    QWidget * InitStatuBar();

    void ChangeActionChecked(MainWindow::MainWindowDialogType);

    QLabel * m_pStatuTimeLabel;
    QLabel * m_pStatuAccountLabel;

    QAction * m_pActionExit;
    QAction * m_pActionUPW;


    QAction * m_pActionSystemManager;
    QAction * m_pActionWeeklyReport;

    QStackedWidget * m_pMainStackWidget;
    SystemManagerDialog * m_pSystemManagerDialog;
    WeeklyReportDialog * m_pWeeklyReportDialog;

};

#endif // MAINWINDOW_H
