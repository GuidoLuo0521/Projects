#ifndef SYSTEMMANAGERDIALOG_H
#define SYSTEMMANAGERDIALOG_H

#include <QMainWindow>
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
    void signalQuery(QString);

private slots:
    void slotShowStaffs();
    void slotShowRole();
    void slotShowDepartment();
    void slotShowJob();

    void slotQuery(QString);

private:
    void BindSlot();
    void ActionChecked(QAction * pAction);

    Ui::SystemManagerDialog *ui;

    QAction * m_pStaffManager;
    QAction * m_pRoleManager;
    QAction * m_pDepartmentManager;
    QAction * m_pJobManager;

    void InitLayout();

    QSqlQueryModel * m_pSqlQueryModel;
    QTableView * m_pTableView;

};

#endif // SYSTEMMANAGERDIALOG_H
