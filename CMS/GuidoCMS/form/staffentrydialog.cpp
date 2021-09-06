#include "staffentrydialog.h"

#include "database/cmsdatebasedef.h"
#include "delegate/controldelegate.h"
#include "controlext/controlext.h"

StaffEntryDialog::StaffEntryDialog(QWidget *parent) :
    EntryAddDialog(parent)
{
    InitLayout();
}

StaffEntryDialog::~StaffEntryDialog()
{
}

void StaffEntryDialog::slotAdd()
{
    if(CheckParams() == false || CheckExist() == true)
        return;

    QString StaffName = m_pLineEditName->Text().toUtf8();
    QString StaffPassword = m_pLineEditPassword->Text().toUtf8();
    if(StaffPassword == "")
        StaffPassword = "666666";

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
    QString Introduction = m_pPlainTextEditDesc->Text();
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
    //QMessageBox::information(this, "提示", "插入成功");

    emit signalAddSuccess(true);
}

void StaffEntryDialog::InitLayout()
{
    setWindowTitle("人员信息");
     ////////////////////////////////////////////////////////////
    // 添加人员
    QGridLayout * pGridLayoutAdd = new QGridLayout;

    /// Name
    m_pLineEditName = new StanderLineEdit("姓名：", "");
    m_pLineEditPassword = new StanderLineEdit("密码：", "");
    m_pLineEditPassword->LineEdit()->setEchoMode(QLineEdit::Password);
    m_pLineEditPassword->LineEdit()->setPlaceholderText("初始密码：666666");
    m_pLineEditWorkingAge = new StanderLineEdit("工龄：", "");
    m_pLineEditWage = new StanderLineEdit("工资：", "");
    m_pLineEditPhone = new StanderLineEdit("电话：", "");
    m_pLineEditEmail = new StanderLineEdit("邮箱：", "");
    m_pLineEditAddress = new StanderLineEdit("住址：", "");
    m_pPlainTextEditDesc = new StanderPlainTextEdit("备注：", "", Qt::Vertical);
    m_pDateEditBirthday = new StanderDateEdit("出生日期：", "1965-01-01");
    m_pDateEditEnterCompany = new StanderDateEdit("入职时间：", QDate::currentDate().toString("yyyy-MM-dd"));
    m_pDateEditLeaveCompany = new StanderDateEdit("出生日期：", "9999-12-31");

    int nRow = 0, nColumn = 0, nRowCount = 0;
    pGridLayoutAdd->addLayout(m_pLineEditName->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditPassword->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditWorkingAge->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditWage->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditPhone->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditEmail->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pLineEditAddress->Layout(), nRow++, nColumn);
    pGridLayoutAdd->addLayout(m_pDateEditBirthday->Layout(), nRow++, nColumn, 1, 3);
    pGridLayoutAdd->addLayout(m_pDateEditEnterCompany->Layout(), nRow++, nColumn, 1, 3);
    pGridLayoutAdd->addLayout(m_pDateEditLeaveCompany->Layout(), nRow++, nColumn, 1, 3);
    pGridLayoutAdd->addLayout(m_pPlainTextEditDesc->Layout(), nRow++, nColumn, 1, 3);

    nRowCount = nRow;

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

    // add button
    pGridLayoutAdd->addLayout(m_pButtonLayout, nRowCount, nColumn);

    this->setLayout(pGridLayoutAdd);
}

bool StaffEntryDialog::CheckParams()
{
    if(m_pLineEditName->Text() == "")
    {
        QMessageBox::warning(this, "提示", "姓名不能为空");
        return false;
    }
    //if(m_pLineEditPassword->Text() == "")
    //{
    //    QMessageBox::warning(this, "提示", "密码不能为空");
    //    return false;
    //}
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

bool StaffEntryDialog::CheckExist()
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

void StaffEntryDialog::slotClear()
{
    m_pLineEditName->LineEdit()->clear();
    m_pLineEditPassword->LineEdit()->clear();
    m_pLineEditWorkingAge->LineEdit()->clear();
    m_pLineEditWage->LineEdit()->clear();
    m_pLineEditPhone->LineEdit()->clear();
    m_pLineEditEmail->LineEdit()->clear();
    m_pLineEditAddress->LineEdit()->clear();
    m_pPlainTextEditDesc->TextEdit()->clear();

    m_pDateEditBirthday->DateEdit()->setDate(QDate::fromString("1965-01-01", Qt::ISODate));
    m_pDateEditEnterCompany->DateEdit()->setDate(QDate::currentDate());
    m_pDateEditLeaveCompany->DateEdit()->setDate(QDate::fromString("9999-12-31", Qt::ISODate));
}

