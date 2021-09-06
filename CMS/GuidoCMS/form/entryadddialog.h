#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDialog>
#include <QComboBox>

#include <QTableView>
#include <QSqlTableModel>

#include "database/cmsdatabase.h"
#include "common/controlinclude.h"

#include <QSplitter>

class EntryAddDialog : public QWidget
{
    Q_OBJECT

public:
    explicit EntryAddDialog(QWidget *parent = nullptr);
    virtual ~EntryAddDialog();

    static QStringList GetDepartmentList();
    static QStringList GetSpecialtyList();
    static QStringList GetEducationList();
    static QStringList GetPlaceList();
    static QStringList GetJobList();
    static QStringList GetRoleList();
    static QStringList GetStateList();
    static QStringList GetSexList();

protected:
    virtual void InitLayout();

signals:
    void signalAddSuccess(bool);

protected slots:
    virtual void slotAdd();
    virtual void slotClear();

protected:
    CMSDatabase * m_pCMSDatabase;

    QHBoxLayout * m_pButtonLayout;
    QPushButton * m_pButtonAdd;
    QPushButton * m_pButtonClear;
};

#endif // TABLEINFODIALOG_H
