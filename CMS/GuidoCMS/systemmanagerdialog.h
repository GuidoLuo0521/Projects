#ifndef SYSTEMMANAGERDIALOG_H
#define SYSTEMMANAGERDIALOG_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QStackedWidget>


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

signals:
    void signalTableChange();

private slots:
    void slotTableChange();

private:
    void InitLayout();
    QWidget* InitToolBar();
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

};

#endif // SYSTEMMANAGERDIALOG_H
