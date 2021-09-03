#include "addtableinfodialog.h"
#include "searchdialog.h"
#include "ui_searchdialog.h"

#include <limits>

SearchDialog::SearchDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog),
    m_bInitOver(false)
{
    ui->setupUi(this);
    InitLayout();
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::SetSearchMode(SearchTableType mode)
{
    m_bInitOver = false;

    Clear();

    switch (mode) {
    case STT_JOB: ShowJob(); break;
    case STT_ROLE: ShowRole(); break;
    case STT_STAFF: ShowStaff(); break;
    case STT_DEPARTMENT: ShowDepartment(); break;
    default:   break;
    }

    m_bInitOver = true;

}

QStringList SearchDialog::GetFilter()
{
    QString strName = ui->leName->text();
    QString strSex = ui->cbSex->currentText();
    QString strState = ui->cbState->currentText();
    QString strDepartment = ui->cbDepartment->currentText();
    QString strJob = ui->cbJob->currentText();
    QString strWageL = ui->sbLower->value() == 0.00 ? "" : ui->sbLower->text();
    QString strWageH = ui->sbHigher->value() == INT_MAX ? "" : ui->sbHigher->text();

    QStringList listFilter;
    listFilter.push_back(strName);
    listFilter.push_back(strSex);
    listFilter.push_back(strDepartment);
    listFilter.push_back(strJob);
    listFilter.push_back(strWageL);
    listFilter.push_back(strWageH);
    listFilter.push_back(strState);

    return listFilter;
}

SearchDialog::SearchTableType SearchDialog::SearchMode()
{
    return m_SearchTableType;
}

void SearchDialog::on_leName_textChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalFilterChange(GetFilter());
}

void SearchDialog::on_cbSex_currentTextChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalFilterChange(GetFilter());
}

void SearchDialog::on_cbDepartment_currentTextChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalFilterChange(GetFilter());
}

void SearchDialog::on_cbJob_currentTextChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalFilterChange(GetFilter());
}

void SearchDialog::on_cbState_currentTextChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalFilterChange(GetFilter());
}

void SearchDialog::Clear()
{
    ui->leName->setText("");
    ui->cbSex->setCurrentIndex(0);
    ui->cbState->setCurrentIndex(0);
    ui->cbDepartment->setCurrentIndex(0);
    ui->cbJob->setCurrentIndex(0);
    ui->sbLower->setValue(0);
    ui->sbHigher->setValue(INT_MAX);
}

void SearchDialog::on_sbLower_valueChanged(double arg1)
{
    if(m_bInitOver)  emit signalFilterChange(GetFilter());
}

void SearchDialog::on_sbHigher_valueChanged(double arg1)
{
    if(m_bInitOver)  emit signalFilterChange(GetFilter());
}

void SearchDialog::on_btnClear_clicked()
{
    Clear();

    if(m_bInitOver)
        emit signalFilterChange(GetFilter());
}

void SearchDialog::InitLayout()
{
    ui->leName->setPlaceholderText("关键字");

    QStringList listSex = AddTableInfoDialog::GetSexList(); listSex.insert(0, "");
    QStringList listJob = AddTableInfoDialog::GetJobList(); listJob.insert(0, "");
    QStringList listState = AddTableInfoDialog::GetStateList(); listState.insert(0, "");
    QStringList listDepartment = AddTableInfoDialog::GetDepartmentList(); listDepartment.insert(0, "");


    ui->cbSex->insertItems(0, listSex);
    ui->cbJob->insertItems(0, listJob);
    ui->cbState->insertItems(0, listState);
    ui->cbDepartment->insertItems(0, listDepartment );

    ui->sbLower->setRange(0, INT_MAX);
    ui->sbLower->setValue(0);

    ui->sbHigher->setRange(0, INT_MAX);
    ui->sbHigher->setValue(INT_MAX);

    m_bInitOver = true;
}

void SearchDialog::HideAll(bool hide)
{
    ui->labelName->setHidden(hide);ui->leName->setHidden(hide);
    ui->labelSex->setHidden(hide);ui->cbSex->setHidden(hide);
    ui->labelDepartment->setHidden(hide);ui->cbDepartment->setHidden(hide);
    ui->labelJob->setHidden(hide);ui->cbJob->setHidden(hide);
    ui->labelState->setHidden(hide);ui->cbState->setHidden(hide);
    ui->labelWageRange->setHidden(hide);ui->sbLower->setHidden(hide);
    ui->sbHigher->setHidden(hide);ui->labelWageRangeTo->setHidden(hide);
}

void SearchDialog::ShowJob()
{
    HideAll(true);
    ui->labelName->setHidden(false);ui->leName->setHidden(false);
    ui->labelState->setHidden(false);ui->cbState->setHidden(false);

    ui->labelName->setText("职务：");
    m_SearchTableType = STT_JOB;
}

void SearchDialog::ShowStaff()
{
    HideAll(false);
    ui->labelState->setHidden(true);ui->cbState->setHidden(true);

    ui->labelName->setText("姓名：");
    m_SearchTableType = STT_STAFF;
}

void SearchDialog::ShowDepartment()
{
    HideAll(true);
    ui->labelName->setHidden(false);ui->leName->setHidden(false);
    ui->labelState->setHidden(false);ui->cbState->setHidden(false);

    ui->labelName->setText("部门：");
    m_SearchTableType = STT_DEPARTMENT;
}
void SearchDialog::ShowRole()
{
    HideAll(true);
    ui->labelName->setHidden(false);ui->leName->setHidden(false);
    ui->labelState->setHidden(false);ui->cbState->setHidden(false);

    ui->labelName->setText("角色：");
    m_SearchTableType = STT_ROLE;
}




