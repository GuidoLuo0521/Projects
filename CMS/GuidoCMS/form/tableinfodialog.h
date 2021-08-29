#ifndef TABLEINFODIALOG_H
#define TABLEINFODIALOG_H

#include <QDialog>
#include <QComboBox>

#include <QTableView>
#include <QSqlTableModel>

#include "database/cmsdatabase.h"

namespace Ui {
class TableInfoDialog;
}

class TableInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableInfoDialog(QWidget *parent = nullptr);
    ~TableInfoDialog();

protected:
    void InitDepartment(QComboBox & combobox);
    void InitSpecialty(QComboBox & combobox);
    void InitEducation(QComboBox & combobox);
    void InitPlace(QComboBox & combobox);
    void InitJob(QComboBox & combobox);

    QTableView * m_pTableView;
    QSqlTableModel * m_pSqlTableModel;
    CMSDatabase * m_pCMSDatabase;

protected:
    virtual void InitLayout();
    virtual void InitTableView();
    virtual void InitTableModel();

private:
    Ui::TableInfoDialog *ui;
};

#endif // TABLEINFODIALOG_H
