#ifndef SYSTEMMANAGERDIALOG_H
#define SYSTEMMANAGERDIALOG_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>


class QStandardItemModel;
class QToolBar;
class QAction;

namespace Ui {
class SystemManagerDialog;
}

class SystemManagerDialog : public QMainWindow
{
    Q_OBJECT

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
    QWidget* InitTableView();
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

    void BindSlot();
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
    QTableView * m_pTableView;

};

#endif // SYSTEMMANAGERDIALOG_H
