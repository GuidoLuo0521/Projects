#ifndef SYSTEMMANAGERDIALOG_H
#define SYSTEMMANAGERDIALOG_H

#include "searchdialog.h"
#include "cmsbasewidget.h"

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

class SystemManagerDialog : public CMSBaseWidget
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

public slots:
    void slotUpdateCurrentPage();

private slots:
    void slotShowSearchDialog(bool bShow);
    void slotShowAddEntryDialog(bool bShow);

    void slotSetTableModelTableJob();
    void slotSetTableModelTableRole();
    void slotSetTableModelTableStaff();
    void slotSetTableModelTableDepartment();

private:
    void InitLayout();
    QWidget* InitMenuBar();
    QWidget* InitToolBar();
    QWidget* InitTableInfoManagerStaff();
    QWidget* InitTableInfoManagerDepartment();
    QWidget* InitTableInfoManagerRole();
    QWidget* InitTableInfoManagerJob();

    void ChangeActionChecked(StackedWidgetType type);

    QAction * m_pActionStaffManager;
    QAction * m_pActionRoleManager;
    QAction * m_pActionDepartmentManager;
    QAction * m_pActionJobManager;

    QAction * m_pActionSearch;
    QAction * m_pActionAddEntry;

    QStackedWidget * m_pStackedWidget;
};

#endif // SYSTEMMANAGERDIALOG_H
