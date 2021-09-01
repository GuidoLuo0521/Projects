#include "addtableinfojobdialog.h"

AddTableInfoJobDialog::AddTableInfoJobDialog(QWidget *parent) :
    AddTableInfoDialog(parent)
{
    InitLayout();
}

AddTableInfoJobDialog::~AddTableInfoJobDialog()
{

}

void AddTableInfoJobDialog::slotAdd()
{
    if(CheckParams() == false)
        return;

    QString strName = m_pLineEditName->LineEdit()->text();
    QString strWage = m_pLineEditBaseWage->LineEdit()->text();
    QString strState = m_pComboBoxState->ComboBox()->currentText();
    QString strDesc = m_pPlainTextEditDesc->PlainText();

    QString strQuery = QString("INSERT INTO job "
                               "VALUES (0, '%1', %2, '%3', '%4', '')")
            .arg(strName).arg(strWage).arg(strState).arg(strDesc);

    m_pCMSDatabase->WDB_Exec(strQuery);

    emit signalAddSuccess(true);
}

void AddTableInfoJobDialog::slotClear()
{
    m_pLineEditName->LineEdit()->clear();
    m_pLineEditBaseWage->LineEdit()->clear();
    m_pComboBoxState->ComboBox()->setCurrentIndex(0);
    m_pPlainTextEditDesc->PlainTextEdit()->clear();
}

void AddTableInfoJobDialog::InitLayout()
{
    setWindowTitle("职务信息");
    QVBoxLayout * pVAddMainLayout = new QVBoxLayout;

    QHBoxLayout * pHBoxLayout0 = new QHBoxLayout;
    m_pLineEditName = new StanderLineEdit("名称：", "", Qt::Horizontal);
    m_pLineEditName->LineEdit()->setPlaceholderText("名称");

    QStringList strList = {"正常", "撤销"};
    m_pComboBoxState = new StanderComboBox("状态：", strList, Qt::Horizontal);

    pHBoxLayout0->addLayout(m_pLineEditName->Layout());
    pHBoxLayout0->addLayout(m_pComboBoxState->Layout());
    //pHBoxLayout0->addStretch();

    QHBoxLayout * pHBoxLayout1 = new QHBoxLayout;
    m_pLineEditBaseWage = new StanderLineEdit("工资：", "", Qt::Horizontal);
    m_pLineEditBaseWage->LineEdit()->setPlaceholderText("0");
    pHBoxLayout1->addLayout(m_pLineEditBaseWage->Layout());
    pHBoxLayout1->addStretch();

    QBoxLayout * pBoxLayout2 = nullptr;
    m_pPlainTextEditDesc = new StanderPlainTextEdit("描述：", "", Qt::Orientation::Vertical);
    pBoxLayout2 = m_pPlainTextEditDesc->Layout();

    pVAddMainLayout->addLayout(pHBoxLayout0);
    pVAddMainLayout->addLayout(pHBoxLayout1);
    pVAddMainLayout->addLayout(pBoxLayout2);
    pVAddMainLayout->addLayout(m_pButtonLayout);
    pVAddMainLayout->addStretch();

    this->setLayout(pVAddMainLayout);
}

bool AddTableInfoJobDialog::CheckParams()
{
    QString strName = m_pLineEditName->LineEdit()->text();
    if(strName == "")
    {
        QMessageBox::warning(this, "警告", "名称不能为空。");
        return false;
    }

    QString strQuery = QString("SELECT JobName FROM job WHERE JobName = '%1'").arg(strName);
    QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

    if (query.next())
    {
        QMessageBox::warning(this, "警告", QString("%1已经存在").arg(strName));
        return false;
    }

    return true;
}
