#ifndef SYSTEMMANAGERDIALOG_H
#define SYSTEMMANAGERDIALOG_H

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
    QWidget* InitTableViewStaff();
    QWidget* InitTableViewDepartment();
    QWidget* InitTableViewRole();
    QWidget* InitTableViewJob();
    QWidget* InitSearchView();

    void InitSqlTableModel();
    void InitSqlTableModelJob();
    void InitSqlTableModelRole();
    void InitSqlTableModelStaff();
    void InitSqlTableModelDepartment();


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

    //QSqlQueryModel * m_pSqlQueryModel;
    QTableView * m_pTableViewStaff;
    QTableView * m_pTableViewDepartment;
    QTableView * m_pTableViewRole;
    QTableView * m_pTableViewJob;

    QStackedWidget * m_pStackedWidget;

    QLabel * m_pStatuTimeLabel;

};

#endif // SYSTEMMANAGERDIALOG_H
