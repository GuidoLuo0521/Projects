#ifndef TABLEMANAGERDIALOG_H
#define TABLEMANAGERDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QMainWindow>

#include "database/cmsdatabase.h"
#include "database/cmsdatebasedef.h"

#include "searchdialog.h"
#include "addtableinfodialog.h"

class TableManagerDialog : public QMainWindow
{
    Q_OBJECT
public:
    TableManagerDialog(QMainWindow * parent = 0);
    virtual ~TableManagerDialog();

protected:

    virtual void CreateAddInforDialog() = 0;

    virtual void InitLayout() = 0;
    virtual void InitTableView() = 0;
    virtual void InitSqlTableModel() = 0;
    virtual void InitSearchDialog() = 0;
    virtual void InitAddTableInfoDialog() = 0;

public slots:
    void slotUpdateTable(bool);

protected slots:
    virtual void slotFilter(QStringList) = 0;

protected:
    SearchDialog * m_pSearchDialog;
    AddTableInfoDialog * m_pAddTableInfoDialog;

    QTableView * m_pTableView;
    QSqlTableModel * m_pSqlTableModel;
};

#endif // TABLEMANAGERDIALOG_H
