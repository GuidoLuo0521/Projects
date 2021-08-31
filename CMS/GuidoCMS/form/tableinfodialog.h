#ifndef TABLEINFODIALOG_H
#define TABLEINFODIALOG_H

#include <QDialog>
#include <QComboBox>

#include <QTableView>
#include <QSqlTableModel>

#include "database/cmsdatabase.h"
#include "common/controlinclude.h"

#include <QSplitter>

namespace Ui {
class TableInfoDialog;
}

class TableInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableInfoDialog(QWidget *parent = nullptr);
    ~TableInfoDialog();

    static QStringList GetDepartmentList();
    static QStringList GetSpecialtyList();
    static QStringList GetEducationList();
    static QStringList GetPlaceList();
    static QStringList GetJobList();
    static QStringList GetStateList();
    static QStringList GetSexList();

protected:
    void InitDepartment(QComboBox & combobox);
    void InitSpecialty(QComboBox & combobox);
    void InitEducation(QComboBox & combobox);
    void InitPlace(QComboBox & combobox);
    void InitJob(QComboBox & combobox);

    virtual void InitLayout();
    virtual void InitTableView();
    virtual void InitTableModel();

private:
    Ui::TableInfoDialog *ui;

protected:
    QTableView * m_pTableView;
    QSqlTableModel * m_pSqlTableModel;
    CMSDatabase * m_pCMSDatabase;
};

#endif // TABLEINFODIALOG_H
