#include "searchdialog.h"
#include "tableinfodialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog),
    m_SearchTableType(STT_NULL),
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
    switch (mode) {
    case STT_JOB: ShowJob(); break;
    case STT_STAFF: ShowStaff(); break;
    case STT_DEPARTMENT: ShowDepartment(); break;
    default:   break;
    }
}

SearchTableType SearchDialog::SearchMode()
{
    return m_SearchTableType;
}

void SearchDialog::on_leName_textChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalNameChange(arg1);
}

void SearchDialog::on_cbSex_currentTextChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalSexChange(arg1);
}

void SearchDialog::on_cbDepartment_currentTextChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalDepartmentChange(arg1);
}

void SearchDialog::on_cbJob_currentTextChanged(const QString &arg1)
{
    if(m_bInitOver)  emit signalJobChange(arg1);
}

void SearchDialog::on_sbLower_valueChanged(double arg1)
{
    if(m_bInitOver)  emit signalRangeChange(arg1, ui->sbHigher->value());
}

void SearchDialog::on_sbHigher_valueChanged(double arg1)
{
    if(m_bInitOver)  emit signalRangeChange(ui->sbLower->value(), arg1);
}

void SearchDialog::on_btnClear_clicked()
{
    if(m_bInitOver) emit signalClear();
}

void SearchDialog::InitLayout()
{
    ui->leName->setPlaceholderText("包含名称");
    ui->cbSex->insertItems(0, TableInfoDialog::GetSexList() );
    ui->cbDepartment->insertItems(0, TableInfoDialog::GetDepartmentList() );
    ui->cbJob->insertItems(0, TableInfoDialog::GetJobList() );

    ui->sbLower->setRange(0, 99999);
    ui->sbLower->setValue(0);

    ui->sbHigher->setRange(0, 99999);
    ui->sbHigher->setValue(99999);

    m_bInitOver = true;
}

void SearchDialog::HideAll(bool hide)
{
    ui->labelName->setHidden(hide);ui->leName->setHidden(hide);
    ui->labelSex->setHidden(hide);ui->cbSex->setHidden(hide);
    ui->labelDepartment->setHidden(hide);ui->cbDepartment->setHidden(hide);
    ui->labelJob->setHidden(hide);ui->cbJob->setHidden(hide);
    ui->labelWageRange->setHidden(hide);ui->sbLower->setHidden(hide);
    ui->sbHigher->setHidden(hide);ui->labelWageRangeTo->setHidden(hide);
}

void SearchDialog::ShowJob()
{
    HideAll(true);
    ui->labelJob->setHidden(false);ui->cbJob->setHidden(false);

    m_SearchTableType = STT_JOB;
}

void SearchDialog::ShowStaff()
{
    HideAll(false);

    m_SearchTableType = STT_STAFF;
}

void SearchDialog::ShowDepartment()
{
    HideAll(true);
    ui->labelDepartment->setHidden(false);ui->cbDepartment->setHidden(false);

    m_SearchTableType = STT_DEPARTMENT;
}




