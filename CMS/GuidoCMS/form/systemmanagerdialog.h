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
    void slotUpdateTable();
    void slotUpdateTime();  

    void slotFilter(QStringList);


private:
    void InitLayout();
    QWidget* InitToolBar();
    QWidget* InitStatuBar();
    QWidget* InitTableViewStaff();
    QWidget* InitTableViewDepartment();
    QWidget* InitTableViewRole();
    QWidget* InitTableViewJob();

    void InitSqlTableModel();
    void InitSqlTableModelJob();
    void InitSqlTableModelRole();
    void InitSqlTableModelStaff();
    void InitSqlTableModelDepartment();

    QSqlTableModel * GetCurrentSqlTableModel();
    void SetTableModelTableJob();
    void SetTableModelTableRole();
    void SetTableModelTableStaff();
    void SetTableModelTableDepartment();

    void ActionChecked(QAction * pAction);

    Ui::SystemManagerDialog *ui;

    QAction * m_pStaffManager;
    QAction * m_pRoleManager;
    QAction * m_pDepartmentManager;
    QAction * m_pJobManager;
    QAction * m_pExit;

    QSqlTableModel * m_pSqlTableModelStaff;
    QSqlTableModel * m_pSqlTableModelDepartment;
    QSqlTableModel * m_pSqlTableModelRole;
    QSqlTableModel * m_pSqlTableModelJob;

    QTableView * m_pTableViewStaff;
    QTableView * m_pTableViewDepartment;
    QTableView * m_pTableViewRole;
    QTableView * m_pTableViewJob;

    QStackedWidget * m_pStackedWidget;
    QDockWidget * m_pSearchDockWidget;
    SearchDialog * m_pSearchDialog;

    QLabel * m_pStatuTimeLabel;
    QLabel * m_pStatuAccountLabel;

};

#endif // SYSTEMMANAGERDIALOG_H
