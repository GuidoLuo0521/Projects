#include "departmentinfodialog.h"
#include "ui_departmentinfodialog.h"


DepartmentInfoDialog::DepartmentInfoDialog(QWidget *parent) :
    TableInfoDialog(parent),
    ui(new Ui::DepartmentInfoDialog)
{
    ui->setupUi(this);

    InitLayout();
    InitTableModel();
    InitTableView();
}

DepartmentInfoDialog::~DepartmentInfoDialog()
{
    delete ui;
}

void DepartmentInfoDialog::slotAdd()
{
    if(CheckParams() == false)
        return;

    QString strName = m_pLineEditName->LineEdit()->text();
    QString strState = m_pComboBoxState->ComboBox()->currentText();
    QString strDesc = m_pPlainTextEditDesc->toPlainText();

    QString strQuery = QString("INSERT INTO department "
                               "VALUES (0, '%1', '%2', '%3', '')")
            .arg(strName).arg(strState).arg(strDesc);

    m_pCMSDatabase->WDB_Exec(strQuery);

    m_pSqlTableModel->select();
    m_pTableView->scrollToBottom();
}

void DepartmentInfoDialog::InitTableModel()
{
    m_pSqlTableModel = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);
    m_pSqlTableModel->setTable(g_listCMSDB_Table_Filed_Department[Department_DepartmentTableName]);

    int i = 0;
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "名称");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "状态");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    //m_pSqlTableModelDepartment->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(Department_DepartmentID, readOnlyDelegate);
    m_pTableView->setItemDelegateForColumn(Department_DepartmentName, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateState = new ComboboxDelegate(this);
    pComboxDelegateState->PushItem("正常");
    pComboxDelegateState->PushItem("撤销");
    m_pTableView->setItemDelegateForColumn(Department_State, pComboxDelegateState);

    m_pSqlTableModel->select();
    m_pSqlTableModel->removeColumn(Department_Param);
}

bool DepartmentInfoDialog::CheckParams()
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
        m_pSqlTableModel->select();
        m_pTableView->scrollToBottom();
        return false;
    }

    return true;
}

void DepartmentInfoDialog::InitTableView()
{
    m_pTableView->setModel(m_pSqlTableModel);
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void DepartmentInfoDialog::InitLayout()
{
    setWindowTitle("部门信息");

    QVBoxLayout * pMainLayout = new QVBoxLayout;

    ////////////////////////////////////////////////////////////
    // 已经存在的部门
    QGroupBox * pGroupBoxExist = new QGroupBox("已有部门");
    QHBoxLayout * pLayoutTableView = new QHBoxLayout;
    m_pTableView = new QTableView;
    m_pTableView->verticalHeader()->hide();
    pLayoutTableView->addWidget(m_pTableView);
    pGroupBoxExist->setLayout(pLayoutTableView);

    ////////////////////////////////////////////////////////////
    // 添加部门
    QGroupBox * pGroupBoxAdd = new QGroupBox("添加部门");

    QVBoxLayout * pVAddMainLayout = new QVBoxLayout;

    QHBoxLayout * pHBoxLayout0 = new QHBoxLayout;
    m_pLineEditName = new StanderLineEdit("名称：", "", Qt::Horizontal);
    m_pLineEditName->LineEdit()->setPlaceholderText("名称");

    QStringList strList = {"正常", "撤销"};
    m_pComboBoxState = new StanderComboBox("状态：", strList, Qt::Horizontal);

    pHBoxLayout0->addLayout(m_pLineEditName->Layout());
    pHBoxLayout0->addLayout(m_pComboBoxState->Layout());
    pHBoxLayout0->addStretch();

    QVBoxLayout * pVBoxLayout = new QVBoxLayout;
    QLabel * pLabelDesc = new QLabel("描述：");
    m_pPlainTextEditDesc = new QPlainTextEdit;
    pVBoxLayout->addWidget(pLabelDesc);
    pVBoxLayout->addWidget(m_pPlainTextEditDesc);

    QHBoxLayout * pHBoxLayout3 = new QHBoxLayout;
    QPushButton * pButtonAdd = new QPushButton("增加");
    QPushButton * pButtonCancle = new QPushButton("退出");
    pHBoxLayout3->addStretch();;
    pHBoxLayout3->addWidget(pButtonAdd);
    pHBoxLayout3->addWidget(pButtonCancle);

    connect(pButtonAdd, &QPushButton::clicked, this, &DepartmentInfoDialog::slotAdd);
    connect(pButtonCancle, &QPushButton::clicked, this, &QDialog::close);

    pVAddMainLayout->addLayout(pHBoxLayout0);
    pVAddMainLayout->addLayout(pVBoxLayout);
    pVAddMainLayout->addLayout(pHBoxLayout3);

    pGroupBoxAdd->setLayout(pVAddMainLayout);

    pMainLayout->addWidget(pGroupBoxExist);
    pMainLayout->addWidget(pGroupBoxAdd);
    this->setLayout(pMainLayout);
}
