#ifndef SYSTEMMANAGERDIALOG_H
#define SYSTEMMANAGERDIALOG_H

#include "searchdialog.h"

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QStackedWidget>
#include <QLabel>


class QStandardItemModel;
class QToolBar;
class QAction;

namespace Ui {
class SystemManagerDialog;
}

class SystemManagerDialog : public QMainWindow
{
    Q_OBJECT

    enum StackedWidgetType
    {
        StaffWidget,
        DepartmentWidget,
        JobWidget,
        RoleWidget,
    };

public:
    explicit SystemManagerDialog(QWidget *parent = nullptr);
    ~SystemManagerDialog();


public slots:
    void slotExitLogin();
    void slotShowWindow();

signals:
    void signalTableChange();
    void signalExitCurrentAccount();

private slots:
    void slotTableChange();
    void slotUpdateTime();  

private:
    void InitLayout();
    QWidget* InitToolBar();
    QWidget* InitStatuBar();
    QWidget* InitTableInfoManagerStaff();
    QWidget* InitTableInfoManagerDepartment();
    QWidget* InitTableInfoManagerRole();
    QWidget* InitTableInfoManagerJob();

    void SetTableModelTableJob();
    void SetTableModelTableRole();
    void SetTableModelTableStaff();
    void SetTableModelTableDepartment();

    void ActionChecked(QAction * pAction);

    QAction * m_pStaffManager;
    QAction * m_pRoleManager;
    QAction * m_pDepartmentManager;
    QAction * m_pJobManager;
    QAction * m_pExit;

    QStackedWidget * m_pStackedWidget;
    QLabel * m_pStatuTimeLabel;
    QLabel * m_pStatuAccountLabel;

};

#endif // SYSTEMMANAGERDIALOG_H
