#include "profiledialog.h"
#include "ui_profiledialog.h"

#include <QMessageBox>
#include "database/cmsdatabase.h"



ProfileDialog::ProfileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileDialog)
{
    ui->setupUi(this);
    m_pCurrentStaff = StaffInfoSingleton::GetInstance();

    setWindowTitle("修改密码 - " + m_pCurrentStaff->GetStaffID() + " " + m_pCurrentStaff->GetStaffName());

    ui->lineEditNewPassword->setPlaceholderText("6 - 20位密码");

    connect(ui->btnCancle, &QPushButton::clicked, this, &ProfileDialog::close);
}

ProfileDialog::~ProfileDialog()
{
    delete ui;
}

void ProfileDialog::on_btnOK_clicked()
{
    if(CheckParam() < 0)
        return;

    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    QString strNewPW = ui->lineEditNewPassword->text();
    QString strQuery = QString("UPDATE Staff SET StaffPassword = '%1' "
                               "WHERE StaffID = '%2'").arg(strNewPW).arg(m_pCurrentStaff->GetStaffID());

    pDB->WDB_Exec(strQuery);

    QMessageBox::information(this, "提示", "更新成功");

    emit signalUpdateSuccess();
    close();
}

int ProfileDialog::CheckParam()
{
    QString strRawPW = ui->lineEditRawPassword->text();
    QString strCekPW = ui->lineEditCheckPassword->text();

    if(strRawPW != m_pCurrentStaff->GetStaffPassword())
    {
        ui->labelTips->setText("原密码错误。");
        return  -1;
    }

    if(strRawPW != strCekPW)
    {
        ui->labelTips->setText("两次输入密码不一致。");
        return  -1;
    }

    QString strNewPW = ui->lineEditNewPassword->text();
    if(strNewPW.length() >= 20)
    {
        QMessageBox::warning(this, "警告", "密码过长");
        return -2;
    }
    if(strNewPW.length() < 6)
    {
        QMessageBox::warning(this, "警告", "密码过短");
        return -2;
    }

    return 1;
}

void ProfileDialog::on_lineEditRawPassword_textChanged(const QString &arg1)
{
    ui->labelTips->setText("");
}

void ProfileDialog::on_lineEditCheckPassword_textChanged(const QString &arg1)
{
    ui->labelTips->setText("");
}

void ProfileDialog::on_lineEditNewPassword_textChanged(const QString &arg1)
{
    if(arg1.count() >= 20)
        ui->labelTips->setText("密码过长，请重新输入。");
    else
        ui->labelTips->setText("");
}
