#ifndef TABLEDATEDIALOG_H
#define TABLEDATEDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QMainWindow>
#include <QDockWidget>

#include "database/cmsdatabase.h"
#include "database/cmsdatebasedef.h"

#include "searchdialog.h"
#include "entryadddialog.h"

class TableDateDialog : public QMainWindow
{
    Q_OBJECT
public:
    TableDateDialog(QMainWindow * parent = 0);
    virtual ~TableDateDialog();

public:
    QDockWidget * getSearchDockWidget();
    QDockWidget * getAddDockWidget();
protected:

    virtual void CreateSpecialDialog();

    virtual void InitTableView();
    virtual void InitLayout();
    virtual void InitSqlTableModel() = 0;
    virtual void InitSearchDialog();
    virtual void InitAddTableInfoDialog();

public slots:
    void slotUpdateTable(bool);

protected slots:
    virtual void slotFilter(QStringList) = 0;

protected:
    QDockWidget * m_pSearchDockWidget;
    QDockWidget * m_pAddDockWidget;

    SearchDialog * m_pSearchDialog;
    EntryAddDialog * m_pAddTableInfoDialog;

    QTableView * m_pTableView;
    QSqlTableModel * m_pSqlTableModel;
};

#endif // TABLEMANAGERDIALOG_H
