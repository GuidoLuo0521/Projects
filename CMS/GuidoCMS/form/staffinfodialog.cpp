#include "staffinfodialog.h"
#include "ui_staffinfodialog.h"

#include "database/cmsdatebasedef.h"
#include "delegate/controldelegate.h"
#include "controlext/controlext.h"

#include <QString>

StaffInfoDialog::StaffInfoDialog(QWidget *parent) :
    TableInfoDialog(parent),
    ui(new Ui::StaffInfoDialog)
{
    ui->setupUi(this);

    InitLayout();
    InitTableModel();
    InitTableView();

}

StaffInfoDialog::~StaffInfoDialog()
{
    delete ui;
}

void StaffInfoDialog::slotAdd()
{
    if(CheckParams() == false || CheckExist() == true)
        return;

    QString StaffName = m_pLineEditName->Text().toUtf8();
    QString StaffPassword = m_pLineEditPassword->Text().toUtf8();
    QString Sex = m_pComboBoxSex->CurrentText().toUtf8();
    QString Birthday = m_pDateEditBirthday->Date().toUtf8();
    QString Department = m_pComboBoxDepartment->CurrentText().toUtf8();
    QString JobName = m_pComboBoxJob->CurrentText().toUtf8();
    float Wage = m_pLineEditWage->Text().toFloat();
    int WorkingAge = m_pLineEditWorkingAge->Text().toInt();;
    QString Place = m_pComboBoxPlace->CurrentText().toUtf8();
    QString Education = m_pComboBoxEducation->CurrentText().toUtf8();
    QString Specialty = m_pComboBoxSpecialty->CurrentText().toUtf8();
    QString Address = m_pLineEditAddress->Text().toUtf8();
    QString EMail = m_pLineEditEmail->Text().toUtf8();
    QString Phone = m_pLineEditPhone->Text().toUtf8();
    QString EnterCampany = m_pDateEditEnterCompany->Date().toUtf8();
    QString LeaveCampany = m_pDateEditLeaveCompany->Date().toUtf8();
    QString Introduction = m_pPlainTextEditDesc->PlainText();
    QString Param = "";

    QString strSql = QString(" INSERT INTO staff "
                              "VALUES (%1,'%2','%3','%4','%5',"
                              "'%6','%7',%8,%9,'%10',"
                              "'%11','%12','%13','%14','%15',"
                              "'%16','%17','%18','%19');")
             .arg(0).arg(StaffName).arg(StaffPassword).arg(Sex).arg(Birthday)
             .arg(Department).arg(JobName).arg(Wage).arg(WorkingAge).arg(Place)
             .arg(Education).arg(Specialty).arg(Address).arg(EMail).arg(Phone)
             .arg(EnterCampany).arg(LeaveCampany).arg(Introduction).arg(Param);

    qDebug() << strSql;
    m_pCMSDatabase->WDB_Exec(strSql);
    QMessageBox::information(this, "提示", "插入成功");

    m_pSqlTableModel->select();
    m_pTableView->scrollToBottom();

    ClearAddControl();
}

void StaffInfoDialog::InitLayout()
{
    setWindowTitle("人员信息");

    ////////////////////////////////////////////////////////////
    // 已经存在的部门
    QGroupBox * pGroupBoxExist = new QGroupBox("已有人员");
    QHBoxLayout * pLayoutTableView = new QHBoxLayout;
    m_pTableView = new QTableView;
    m_pTableView->verticalHeader()->hide();
    pLayoutTableView->addWidget(m_pTableView);
    pGroupBoxExist->setLayout(pLayoutTableView);

    ////////////////////////////////////////////////////////////
    // 添加人员
    QGroupBox * pGroupBoxAdd = new QGroupBox("添加人员");
    QGridLayout * pGridLayoutAdd = new QGridLayout;

    /// Name
    m_pLineEditName = new StanderLineEdit("名称：", "");
    m_pLineEditPassword = new StanderLineEdit("密码：", "666666");
    m_pLineEditPassword->LineEdit()->setEchoMode(QLineEdit::Password);
    m_pLineEditWorkingAge = new StanderLineEdit("工龄：", "");
    m_pLineEditWage = new StanderLineEdit("工资：", "");
    m_pLineEditPhone = new StanderLineEdit("电话：", "");
    m_pLineEditEmail = new StanderLineEdit("邮箱：", "");
    m_pLineEditAddress = new StanderLineEdit("住址：", "");
    m_pPlainTextEditDesc = new StanderPlainTextEdit("备注：", "", Qt::Vertical);

    int nRow = 0, nColumn = 0;
    pGridLayoutAdd->addLayout(m_pLineEditName->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditPassword->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditWorkingAge->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditWage->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditPhone->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditEmail->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditAddress->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pPlainTextEditDesc->Layout(), nRow++, nColumn, 1, 5);

    m_pComboBoxSex = new StanderComboBox( "性别：", GetSexList());
    m_pComboBoxPlace = new StanderComboBox( "籍贯：", GetPlaceList());
    m_pComboBoxDepartment = new StanderComboBox( "部门：", GetDepartmentList());
    m_pComboBoxJob = new StanderComboBox( "职务：", GetJobList());
    m_pComboBoxEducation = new StanderComboBox( "学历：", GetEducationList());
    m_pComboBoxSpecialty = new StanderComboBox( "专业：", GetSpecialtyList());

    nRow = 0, nColumn++;
    pGridLayoutAdd->addLayout(m_pComboBoxSex->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pComboBoxPlace->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pComboBoxDepartment->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pComboBoxJob->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pComboBoxEducation->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pComboBoxSpecialty->Layout(), nRow++, nColumn);

    nRow = 0, nColumn++;
    m_pDateEditBirthday = new StanderDateEdit("出生日期：", "1965-01-01");
    m_pDateEditEnterCompany = new StanderDateEdit("入职时间：", QDate::currentDate().toString("yyyy-MM-dd"));
    m_pDateEditLeaveCompany = new StanderDateEdit("出生日期：", "9999-12-31");
    pGridLayoutAdd->addLayout(m_pDateEditBirthday->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pDateEditEnterCompany->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pDateEditLeaveCompany->Layout(), nRow++, nColumn);

    //nRow = 0, nColumn++;
    //pGridLayoutAdd->addItem( new QSpacerItem(40, 20), nRow++, nColumn);

    nRow = 8;
    QHBoxLayout * pHBoxLayoutButton = new QHBoxLayout;
    QPushButton * pButtonAdd = new QPushButton("增加");
    QPushButton * pButtonCancle = new QPushButton("退出");
    pHBoxLayoutButton->addWidget(pButtonAdd);
    pHBoxLayoutButton->addWidget(pButtonCancle);

    connect(pButtonAdd, &QPushButton::clicked, this, &StaffInfoDialog::slotAdd);
    connect(pButtonCancle, &QPushButton::clicked, this, &QDialog::close);    
    pGridLayoutAdd->addLayout(pHBoxLayoutButton, nRow, nColumn);

    pGroupBoxAdd->setLayout(pGridLayoutAdd);

    QVBoxLayout * pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(pGroupBoxExist);
    pMainLayout->addWidget(pGroupBoxAdd);

    this->setLayout(pMainLayout);

}


void StaffInfoDialog::InitTableView()
{
    m_pTableView->setModel(m_pSqlTableModel);
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void StaffInfoDialog::InitTableModel()
{
    m_pSqlTableModel = new QSqlTableModel(this, CMSDatabaseSingleton::GetInstance()->m_WebDatabase);
    m_pSqlTableModel->setTable(g_listCMSDB_Table_Filed_Staff[Staff_StaffTableName]);

    int i = 0;
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "编号");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "姓名");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "密码");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "性别");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "生日");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "部门");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "职务");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "工资");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "工龄");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "籍贯");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "学历");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "专业");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "住址");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "邮件");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "电话");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "入职时间");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "离职时间");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "描述");
    m_pSqlTableModel->setHeaderData(i++, Qt::Orientation::Horizontal, "备注");

    // 设置0列只读
    ReadOnlyDelegate * readOnlyDelegate = new ReadOnlyDelegate(this);
    m_pTableView->setItemDelegateForColumn(Staff_StaffID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateSex = new ComboboxDelegate(this);
    pComboxDelegateSex->PushItem("男性");
    pComboxDelegateSex->PushItem("女性");
    pComboxDelegateSex->PushItem("未知");
    m_pTableView->setItemDelegateForColumn(Staff_Sex, pComboxDelegateSex);

    DateDelegate * pBirthdayDelegate = new DateDelegate(this);
    m_pTableView->setItemDelegateForColumn(Staff_Birthday, pBirthdayDelegate);

    ComboboxDelegate * pComboxDelegateDepartment = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
        pComboxDelegateDepartment->PushItem(g_strListDepartment[i]);
    m_pTableView->setItemDelegateForColumn(Staff_Department, pComboxDelegateDepartment);

    ComboboxDelegate * pComboxDelegatePlace = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListPlace.size(); ++i)
        pComboxDelegatePlace->PushItem(g_strListPlace[i]);
    m_pTableView->setItemDelegateForColumn(Staff_Place, pComboxDelegatePlace);

    ComboboxDelegate * pComboxDelegateEducation = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListEducation.size(); ++i)
        pComboxDelegateEducation->PushItem(g_strListEducation[i]);
    m_pTableView->setItemDelegateForColumn(Staff_Education, pComboxDelegateEducation);

    ComboboxDelegate * pComboxDelegateSpecialty = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListSpecialty.size(); ++i)
        pComboxDelegateSpecialty->PushItem(g_strListSpecialty[i]);
    m_pTableView->setItemDelegateForColumn(Staff_Specialty, pComboxDelegateSpecialty);

    ComboboxDelegate * pComboxDelegateJobName = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
    {
        QString str = g_strListDepartment[i];
        str.remove("部");
        pComboxDelegateJobName->PushItem(str);
    }
    m_pTableView->setItemDelegateForColumn(Staff_JobName, pComboxDelegateJobName);

    DateDelegate * pDelegateEnter = new DateDelegate(this);
    m_pTableView->setItemDelegateForColumn(Staff_EnterCompany, pDelegateEnter);

    DateDelegate * pDelegateLeave = new DateDelegate(this);
    m_pTableView->setItemDelegateForColumn(Staff_LeaveCompany, pDelegateLeave);

    m_pSqlTableModel->select();
}

bool StaffInfoDialog::CheckParams()
{
    if(m_pLineEditName->Text() == "")
    {
        QMessageBox::warning(this, "提示", "姓名不能为空");
        return false;
    }
    if(m_pLineEditPassword->Text() == "")
    {
        QMessageBox::warning(this, "提示", "密码不能为空");
        return false;
    }
    if(m_pLineEditWorkingAge->Text() == "")
    {
        QMessageBox::warning(this, "提示", "工龄不能为空");
        return false;
    }
    if(m_pLineEditWage->Text() == "")
    {
        QMessageBox::warning(this, "提示", "工资不能为空");
        return false;
    }

    return true;
}

bool StaffInfoDialog::CheckExist()
{
    QString StaffName = m_pLineEditName->Text().toUtf8();
    QString Sex = m_pComboBoxSex->CurrentText().toUtf8();
    QString Birthday = m_pDateEditBirthday->Date().toUtf8();

    QString strSql = QString(" SELECT StaffName, Sex, Birthday FROM staff "
                             "WHERE StaffName = '%1' AND Sex = '%2' AND Birthday = '%3';")
             .arg(StaffName).arg(Sex).arg(Birthday);

    qDebug() << strSql;
    QSqlQuery query = m_pCMSDatabase->WDB_Exec(strSql);

    if(query.next())
    {
        if( QMessageBox::warning(
                    this,
                    "警告",
                    QString("已经存在名为%1，生日为%3的%2，是否还要添加?").arg(StaffName).arg(Sex).arg(Birthday),
                    QMessageBox::Yes,
                    QMessageBox::No) == QMessageBox::Yes )
            return false;
        else
            return true;
    }
    return false;
}

void StaffInfoDialog::ClearAddControl()
{
    m_pLineEditName->LineEdit()->clear();
    m_pLineEditPassword->LineEdit()->clear();
    m_pLineEditWorkingAge->LineEdit()->clear();
    m_pLineEditWage->LineEdit()->clear();
    m_pLineEditPhone->LineEdit()->clear();
    m_pLineEditEmail->LineEdit()->clear();
    m_pLineEditAddress->LineEdit()->clear();
    m_pPlainTextEditDesc->PlainTextEdit()->clear();


    m_pDateEditBirthday->DateEdit()->setDate(QDate::fromString("1965-01-01", Qt::ISODate));
    m_pDateEditEnterCompany->DateEdit()->setDate(QDate::currentDate());
    m_pDateEditLeaveCompany->DateEdit()->setDate(QDate::fromString("9999-12-31", Qt::ISODate));
}

