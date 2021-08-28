#ifndef STAFFINFODIALOG_H
#define STAFFINFODIALOG_H

#include <QComboBox>
#include <QDialog>
#include "common/staffinfo.h"
#include "database/cmsdatabase.h"

namespace Ui {
class StaffInfoDialog;
}

class StaffInfoDialog : public QDialog
{
    Q_OBJECT

public:
    // 如果为空，则为增加，不为空，则为修改
    explicit StaffInfoDialog(CStaffInfo * pStaffInfo = nullptr, QWidget *parent = nullptr);
    ~StaffInfoDialog();


private slots:
    void on_btnAdd_clicked();

private:
    // 部门
    void InitDepartment();
    // 专业
    void InitSpecialty();
    // 教育
    void InitEducation();
    // 籍贯
    void InitPlace();
    // 职务
    void InitJob();


    void InsertStaff();
    void UpdateStaff();

    bool CheckParams();

private:
    Ui::StaffInfoDialog *ui;
    CMSDatabase * m_pCMSDatabase;
    CStaffInfo * m_pStaffInfo;

};

#endif // STAFFINFODIALOG_H
