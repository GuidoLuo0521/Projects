#include "staffinfodialog.h"
#include "ui_staffinfodialog.h"

#include "database/cmsdatebasedef.h"
#include "delegate/controldelegate.h"

#include <QString>


StaffInfoDialog::StaffInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StaffInfoDialog),
    m_pCMSDatabase(nullptr)
{
    ui->setupUi(this);

    m_pCMSDatabase = CMSDatabaseSingleton::GetInstance();

    setWindowTitle("人员管理");
    ui->btnAdd->setText("增加");
    ui->lePassword->setText("666666");
    ui->deLeaveDate->setDate(QDate::fromString("9999-12-31", Qt::ISODate));

    InitSqlModel();
    InitTableView();

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

        int nIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("DepartmentName").toString();
            ui->cbDepartment->insertItem(nIndex, name);

            nIndex++;
        }
    }
}

void StaffInfoDialog::InitSpecialty()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbSpecialty->clear();

        QString strQuery = "SELECT Name FROM Specialty";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("Name").toString();
            ui->cbSpecialty->insertItem(nIndex, name);
            nIndex++;
        }
    }
}

void StaffInfoDialog::InitEducation()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbEducation->clear();

        QString strQuery = "SELECT Name FROM education";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("Name").toString();
            ui->cbEducation->insertItem(nIndex, name);
            nIndex++;
        }
    }
}

void StaffInfoDialog::InitPlace()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbPlace->clear();

        QString strQuery = "SELECT Province, City FROM place";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString place, Province = "",  City = "";
        while (query.next())
        {
            Province = query.value("Province").toString();
            City = query.value("City").toString();

            place = Province+City;
            ui->cbPlace->insertItem(nIndex, place);
            nIndex++;
        }
    }
}

void StaffInfoDialog::InitJob()
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        ui->cbJob->clear();

        QString strQuery = "SELECT JobName FROM job";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("JobName").toString();
            ui->cbJob->insertItem(nIndex, name);
            nIndex++;
        }
    }
}

void StaffInfoDialog::InitTableView()
{
    ui->tableView->setModel(m_pSqlTableModel);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void StaffInfoDialog::InitSqlModel()
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
    ui->tableView->setItemDelegateForColumn(Staff_StaffID, readOnlyDelegate);

    ComboboxDelegate * pComboxDelegateSex = new ComboboxDelegate(this);
    pComboxDelegateSex->PushItem("男性");
    pComboxDelegateSex->PushItem("女性");
    pComboxDelegateSex->PushItem("未知");
    ui->tableView->setItemDelegateForColumn(Staff_Sex, pComboxDelegateSex);

    DateDelegate * pBirthdayDelegate = new DateDelegate(this);
    ui->tableView->setItemDelegateForColumn(Staff_Birthday, pBirthdayDelegate);

    ComboboxDelegate * pComboxDelegateDepartment = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
        pComboxDelegateDepartment->PushItem(g_strListDepartment[i]);
    ui->tableView->setItemDelegateForColumn(Staff_Department, pComboxDelegateDepartment);

    ComboboxDelegate * pComboxDelegatePlace = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListPlace.size(); ++i)
        pComboxDelegatePlace->PushItem(g_strListPlace[i]);
    ui->tableView->setItemDelegateForColumn(Staff_Place, pComboxDelegatePlace);

    ComboboxDelegate * pComboxDelegateEducation = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListEducation.size(); ++i)
        pComboxDelegateEducation->PushItem(g_strListEducation[i]);
    ui->tableView->setItemDelegateForColumn(Staff_Education, pComboxDelegateEducation);

    ComboboxDelegate * pComboxDelegateSpecialty = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListSpecialty.size(); ++i)
        pComboxDelegateSpecialty->PushItem(g_strListSpecialty[i]);
    ui->tableView->setItemDelegateForColumn(Staff_Specialty, pComboxDelegateSpecialty);

    ComboboxDelegate * pComboxDelegateJobName = new ComboboxDelegate(this);
    for(int i = 0; i < g_strListDepartment.size(); ++i)
    {
        QString str = g_strListDepartment[i];
        str.remove("部");
        pComboxDelegateJobName->PushItem(str);
    }
    ui->tableView->setItemDelegateForColumn(Staff_JobName, pComboxDelegateJobName);

    DateDelegate * pDelegateEnter = new DateDelegate(this);
    ui->tableView->setItemDelegateForColumn(Staff_EnterCompany, pDelegateEnter);

    DateDelegate * pDelegateLeave = new DateDelegate(this);
    ui->tableView->setItemDelegateForColumn(Staff_LeaveCompany, pDelegateLeave);

    m_pSqlTableModel->select();
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

    m_pSqlTableModel->select();
    ui->tableView->selectRow(m_pSqlTableModel->rowCount() - 1);
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
    {
        InsertStaff();
    }
}
