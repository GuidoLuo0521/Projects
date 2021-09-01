#include "addtableinfodepartmentdialog.h"


AddTableInfoDepartmentDialog::AddTableInfoDepartmentDialog(QWidget *parent) :
    AddTableInfoDialog(parent)
{
    InitLayout();
}

AddTableInfoDepartmentDialog::~AddTableInfoDepartmentDialog()
{

}

void AddTableInfoDepartmentDialog::slotAdd()
{
    if(CheckParams() == false)
        return;

    QString strName = m_pLineEditName->LineEdit()->text();
    QString strState = m_pComboBoxState->ComboBox()->currentText();
    QString strDesc = m_pPlainTextEditDesc->PlainText();

    QString strQuery = QString("INSERT INTO department "
                               "VALUES (0, '%1', '%2', '%3', '')")
            .arg(strName).arg(strState).arg(strDesc);

    m_pCMSDatabase->WDB_Exec(strQuery);

    emit signalAddSuccess(true);
}

void AddTableInfoDepartmentDialog::slotClear()
{
    m_pLineEditName->LineEdit()->clear();
    m_pComboBoxState->ComboBox()->setCurrentIndex(0);
    m_pPlainTextEditDesc->PlainTextEdit()->clear();
}

bool AddTableInfoDepartmentDialog::CheckParams()
{
    QString strName = m_pLineEditName->LineEdit()->text();
    if(strName == "")
    {
        QMessageBox::warning(this, "警告", "名称不能为空。");
        return false;
    }

    QString strQuery = QString("SELECT DepartmentName FROM department WHERE DepartmentName = '%1'").arg(strName);
    QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

    if (query.next())
    {
        QMessageBox::warning(this, "警告", QString("%1已经存在").arg(strName));
        return false;
    }

    return true;
}

void AddTableInfoDepartmentDialog::InitLayout()
{
    setWindowTitle("部门信息");
    QVBoxLayout * pVAddMainLayout = new QVBoxLayout;

    QHBoxLayout * pHBoxLayout0 = new QHBoxLayout;
    m_pLineEditName = new StanderLineEdit("名称：", "", Qt::Horizontal);
    m_pLineEditName->LineEdit()->setPlaceholderText("名称");

    QStringList strList = {"正常", "撤销"};
    m_pComboBoxState = new StanderComboBox("状态：", strList, Qt::Horizontal);

    pHBoxLayout0->addLayout(m_pLineEditName->Layout());
    pHBoxLayout0->addLayout(m_pComboBoxState->Layout());
    pHBoxLayout0->addStretch();

    m_pPlainTextEditDesc = new StanderPlainTextEdit("描述", "", Qt::Orientation::Vertical);

    pVAddMainLayout->addLayout(pHBoxLayout0);
    pVAddMainLayout->addLayout(m_pPlainTextEditDesc->Layout());
    pVAddMainLayout->addLayout(m_pButtonLayout);
    pVAddMainLayout->addStretch();

    this->setLayout(pVAddMainLayout);
}
