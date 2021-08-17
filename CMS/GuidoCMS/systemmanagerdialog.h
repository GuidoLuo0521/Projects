#ifndef SYSTEMMANAGERDIALOG_H
#define SYSTEMMANAGERDIALOG_H

#include <QMainWindow>


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

private:
    Ui::SystemManagerDialog *ui;

    QAction * m_pStaffManager;
    QAction * m_pRoleManager;
    QAction * m_pDepartmentManager;
    QAction * m_pJobManager;

    void InitLayout();

    QStandardItemModel * m_pStandardItemModel;


};

#endif // SYSTEMMANAGERDIALOG_H
