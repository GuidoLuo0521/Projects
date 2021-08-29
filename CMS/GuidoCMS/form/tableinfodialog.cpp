#include "tableinfodialog.h"
#include "ui_tableinfodialog.h"


#include <QGridLayout>

TableInfoDialog::TableInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableInfoDialog),
    m_pSqlTableModel(nullptr),
    m_pTableView(nullptr),
    m_pCMSDatabase(nullptr)
{
    ui->setupUi(this);
    m_pCMSDatabase = CMSDatabaseSingleton::GetInstance();
}

TableInfoDialog::~TableInfoDialog()
{
    delete ui;
}

void TableInfoDialog::InitTableView()
{
    if(m_pSqlTableModel == nullptr)
        InitTableModel();

    m_pTableView->setModel(m_pSqlTableModel);
    m_pTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    /*
    m_pTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_pTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    */
}

void TableInfoDialog::InitTableModel()
{
    m_pSqlTableModel = new QSqlTableModel;
}

void TableInfoDialog::InitDepartment(QComboBox & combobox)
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        combobox.clear();

        QString strQuery = "SELECT DepartmentName FROM department";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("DepartmentName").toString();
            combobox.insertItem(nIndex, name);
            nIndex++;
        }
    }
}
void TableInfoDialog::InitSpecialty(QComboBox & combobox)
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        combobox.clear();

        QString strQuery = "SELECT Name FROM Specialty";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("Name").toString();
            combobox.insertItem(nIndex, name);
            nIndex++;
        }
    }
}
void TableInfoDialog::InitEducation(QComboBox & combobox)
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        combobox.clear();

        QString strQuery = "SELECT Name FROM education";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("Name").toString();
            combobox.insertItem(nIndex, name);
            nIndex++;
        }
    }
}
void TableInfoDialog::InitPlace(QComboBox & combobox)
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        combobox.clear();

        QString strQuery = "SELECT Province, City FROM place";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString place, Province = "",  City = "";
        while (query.next())
        {
            Province = query.value("Province").toString();
            City = query.value("City").toString();

            place = Province+City;
            combobox.insertItem(nIndex, place);
            nIndex++;
        }
    }
}
void TableInfoDialog::InitJob(QComboBox & combobox)
{
    if(m_pCMSDatabase && m_pCMSDatabase->WDB_IsOpen())
    {
        combobox.clear();

        QString strQuery = "SELECT JobName FROM job";
        QSqlQuery query = m_pCMSDatabase->WDB_Exec(strQuery);

        int nIndex = 0;
        QString name = "";
        while (query.next())
        {
            name = query.value("JobName").toString();
            combobox.insertItem(nIndex, name);
            nIndex++;
        }
    }
}

void TableInfoDialog::InitLayout()
{
    QGridLayout * pMainLayout = new QGridLayout;
    m_pTableView = new QTableView;
    pMainLayout->addWidget(m_pTableView);

    this->setLayout(pMainLayout);
}
