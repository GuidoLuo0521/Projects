#include "staffinfodialog.h"
#include "ui_staffinfodialog.h"

#include <QString>


StaffInfoDialog::StaffInfoDialog(CStaffInfo *pStaffInfo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StaffInfoDialog),
    m_pCMSDatabase(nullptr),
    m_pStaffInfo(pStaffInfo)
{
    ui->setupUi(this);

    m_pCMSDatabase = CMSDatabaseSingleton::GetInstance();

    if(m_pStaffInfo )
    {
        setWindowTitle("修改个人信息 " + m_pStaffInfo->GetStaffName());

        ui->leName->setText(m_pStaffInfo->GetStaffName());
        ui->cbSex->setCurrentText(m_pStaffInfo->GetSex());
        ui->lePassword->setText(m_pStaffInfo->GetStaffPassword());
        ui->lePhone->setText(m_pStaffInfo->GetPhone());
        ui->leWage->setText(QString::number(m_pStaffInfo->GetWage()));
        ui->leWorkingAge->setText(QString::number(m_pStaffInfo->GetWorkingAge()));
        ui->leEmail->setText(m_pStaffInfo->GetEmail());
        ui->leAddress->setText(m_pStaffInfo->GetAddress());
        ui->teIntroduce->setPlainText(m_pStaffInfo->GetIntroduction());

        ui->dateTimeEditBirthday->setDate(QDate::fromString(m_pStaffInfo->GetBirthday(), Qt::ISODate));
        ui->deEnterDate->setDate(QDate::fromString(m_pStaffInfo->GetEnterCampany(), Qt::ISODate));
        ui->deLeaveDate->setDate(QDate::fromString(m_pStaffInfo->GetLeaveCampany(), Qt::ISODate));

        ui->btnAdd->setText("修改");
    }
    else
    {
        setWindowTitle("增加个人信息");

        ui->btnAdd->setText("增加");
        ui->lePassword->setText("666666");
        ui->deLeaveDate->setDate(QDate::fromString("9999-12-31", Qt::ISODate));
    }

    InitDepartment();
    InitSpecialty();
    InitEducation();
    InitPlace();
    InitJob();

    connect( ui->btnCancle, &QPushButton::clicked, this, &StaffInfoDialog::close);
}

StaffInfoDialog::~StaffInfoDialog()
{
    delete ui;
}

void StaffInfoDialog::InitDepartment()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbDepartment->clear();

        QString strQuery = "SELECT DepartmentName FROM department";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0, nSeletIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("DepartmentName").toString();
            ui->cbDepartment->insertItem(nIndex, name);

            if(m_pStaffInfo && name == m_pStaffInfo->GetDepartment())
            {
                nSeletIndex = nIndex;
            }

            nIndex++;
        }

        ui->cbDepartment->setCurrentIndex(nSeletIndex);
    }
}

void StaffInfoDialog::InitSpecialty()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbSpecialty->clear();

        QString strQuery = "SELECT Name FROM Specialty";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0, nSeletIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("Name").toString();
            ui->cbSpecialty->insertItem(nIndex, name);

            if(m_pStaffInfo && name == m_pStaffInfo->GetSpecialty())
            {
                nSeletIndex = nIndex;
            }

            nIndex++;
        }

        ui->cbSpecialty->setCurrentIndex(nSeletIndex);
    }
}

void StaffInfoDialog::InitEducation()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbEducation->clear();

        QString strQuery = "SELECT Name FROM education";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0, nSeletIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("Name").toString();
            ui->cbEducation->insertItem(nIndex, name);

            if(m_pStaffInfo && name == m_pStaffInfo->GetEducation())
            {
                nSeletIndex = nIndex;
            }

            nIndex++;
        }

        ui->cbEducation->setCurrentIndex(nSeletIndex);
    }
}

void StaffInfoDialog::InitPlace()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbPlace->clear();

        QString strQuery = "SELECT Province, City FROM place";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0, nSeletIndex = 0;
        QString place, Province = "",  City = "";
        while (query.next())
        {
            Province = query.value("Province").toString();
            City = query.value("City").toString();

            place = Province+City;
            ui->cbPlace->insertItem(nIndex, place);

            if(m_pStaffInfo && place == m_pStaffInfo->GetPlace())
            {
                nSeletIndex = nIndex;
            }

            nIndex++;
        }

        ui->cbPlace->setCurrentIndex(nSeletIndex);
    }
}

void StaffInfoDialog::InitJob()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbJob->clear();

        QString strQuery = "SELECT JobName FROM job";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0, nSeletIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("JobName").toString();
            ui->cbJob->insertItem(nIndex, name);

            if(m_pStaffInfo && name == m_pStaffInfo->GetJobName())
            {
                nSeletIndex = nIndex;
            }

            nIndex++;
        }

        ui->cbJob->setCurrentIndex(nSeletIndex);
    }
}

void StaffInfoDialog::InsertStaff()
{
    QString StaffName = ui->leName->text().toUtf8();
    QString StaffPassword = ui->lePassword->text().toUtf8();
    QString Sex = ui->cbSex->currentText().toUtf8();
    QString Birthday = ui->dateTimeEditBirthday->date().toString("yyyy-MM-dd").toUtf8();
    QString Department = ui->cbDepartment->currentText().toUtf8();
    QString JobName = ui->cbJob->currentText().toUtf8();
    float Wage = ui->leWage->text().toFloat();
    int WorkingAge = ui->leWorkingAge->text().toInt();;
    QString Place = ui->cbPlace->currentText().toUtf8();
    QString Education = ui->cbEducation->currentText().toUtf8();
    QString Specialty = ui->cbSpecialty->currentText().toUtf8();
    QString Address = ui->leAddress->text().toUtf8();
    QString EMail = ui->leEmail->text().toUtf8();
    QString Phone = ui->lePhone->text().toUtf8();
    QString EnterCampany = ui->deEnterDate->date().toString("yyyy-MM-dd").toUtf8();
    QString LeaveCampany = ui->deLeaveDate->date().toString("yyyy-MM-dd").toUtf8();
    QString Introduction = ui->teIntroduce->toPlainText();
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
}

void StaffInfoDialog::UpdateStaff()
{
    QString StaffName = ui->leName->text().toUtf8();
    QString StaffPassword = ui->lePassword->text().toUtf8();
    QString Sex = ui->cbSex->currentText().toUtf8();
    QString Birthday = ui->dateTimeEditBirthday->date().toString("yyyy-MM-dd").toUtf8();
    QString Department = ui->cbDepartment->currentText().toUtf8();
    QString JobName = ui->cbJob->currentText().toUtf8();
    float Wage = ui->leWage->text().toFloat();
    int WorkingAge = ui->leWorkingAge->text().toInt();;
    QString Place = ui->cbPlace->currentText().toUtf8();
    QString Education = ui->cbEducation->currentText().toUtf8();
    QString Specialty = ui->cbSpecialty->currentText().toUtf8();
    QString Address = ui->leAddress->text().toUtf8();
    QString EMail = ui->leEmail->text().toUtf8();
    QString Phone = ui->lePhone->text().toUtf8();
    QString EnterCampany = ui->deEnterDate->date().toString("yyyy-MM-dd").toUtf8();
    QString LeaveCampany = ui->deLeaveDate->date().toString("yyyy-MM-dd").toUtf8();
    QString Introduction = ui->teIntroduce->toPlainText();
    QString Param = "";

    QString strSql = QString(" UPDATE staff "
                             "SET StaffName = '%1', StaffPassword = '%2', Sex = '%3', Birthday = '%4', "
                             "Department = '%5', JobName = '%6', Wage = %7, WorkingAge = %8, Place = '%9',Education = '%10', "
                             "Specialty = '%11', Address = '%12', Email = '%13', Phone = '%14', EnterCompany = '%15', "
                             "LeaveCompany = '%16', Introduction = '%17' "
                             "WHERE staffid = '%18';")
             .arg(StaffName).arg(StaffPassword).arg(Sex).arg(Birthday)
             .arg(Department).arg(JobName).arg(Wage).arg(WorkingAge).arg(Place)
             .arg(Education).arg(Specialty).arg(Address).arg(EMail).arg(Phone)
             .arg(EnterCampany).arg(LeaveCampany).arg(Introduction)
             .arg(m_pStaffInfo->GetStaffID());

    qDebug() << strSql;
    m_pCMSDatabase->WDB_Exec(strSql);

    QMessageBox::information(this, "提示", "修改成功");
}

bool StaffInfoDialog::CheckParams()
{
    if(ui->leName->text() == "")
    {
        QMessageBox::warning(this, "提示", "姓名不能为空");
        return false;
    }
    if(ui->lePassword->text() == "")
    {
        QMessageBox::warning(this, "提示", "密码不能为空");
        return false;
    }
    if(ui->leWorkingAge->text() == "")
    {
        QMessageBox::warning(this, "提示", "工龄不能为空");
        return false;
    }
    if(ui->leWage->text() == "")
    {
        QMessageBox::warning(this, "提示", "工资不能为空");
        return false;
    }

    return true;
}


void StaffInfoDialog::on_btnAdd_clicked()
{
    if(CheckParams())
        m_pStaffInfo ? UpdateStaff() : InsertStaff();

    close();
}
