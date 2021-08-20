#include "systemmanagerdialog.h"
#include "ui_systemmanagerdialog.h"
#include "staffinfo.h"
#include "cmsdatabase.h"

#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QStandardItemModel>

#include "datedelegate.h"
#include "comboxdelegate.h"

SystemManagerDialog::SystemManagerDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemManagerDialog)
{
    ui->setupUi(this);

    InitLayout();
    BindSlot();

    slotShowStaffs();
}

SystemManagerDialog::~SystemManagerDialog()
{
    delete ui;
}

void SystemManagerDialog::slotShowStaffs()
{
    QString query = "select * from staff";

    ActionChecked(m_pStaffManager);
    emit signalQuery(query);
}

void SystemManagerDialog::slotShowRole()
{
    QString query = "select * from role";

    ActionChecked(m_pRoleManager);
    emit signalQuery(query);
}

void SystemManagerDialog::slotShowDepartment()
{
    QString query = "select * from department";

    ActionChecked(m_pDepartmentManager);
    emit signalQuery(query);
}

void SystemManagerDialog::slotShowJob()
{
    QString query = "select * from job";

    ActionChecked(m_pJobManager);
    emit signalQuery(query);
}

void SystemManagerDialog::slotQuery(QString query)
{
    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();
    if(pDB->WDB_IsOpen())
    {
        m_pSqlQueryModel->setQuery( query, pDB->m_WebDatabase);
        m_pTableView->setModel(m_pSqlQueryModel);
    }
}

void SystemManagerDialog::BindSlot()
{
    connect( m_pStaffManager, &QAction::triggered, this, &SystemManagerDialog::slotShowStaffs);
    connect( m_pRoleManager, &QAction::triggered, this, &SystemManagerDialog::slotShowRole);
    connect( m_pJobManager, &QAction::triggered, this, &SystemManagerDialog::slotShowJob);
    connect( m_pDepartmentManager, &QAction::triggered, this, &SystemManagerDialog::slotShowDepartment);

    connect( this, &SystemManagerDialog::signalQuery, this, &SystemManagerDialog::slotQuery);
}

void SystemManagerDialog::ActionChecked(QAction * pAction)
{
    m_pStaffManager->setChecked(false);
    m_pRoleManager->setChecked(false);
    m_pDepartmentManager->setChecked(false);
    m_pJobManager->setChecked(false);

    pAction->setChecked(true);
}

void SystemManagerDialog::InitLayout()
{
    QToolBar* pToolbarMain =  this->addToolBar("管理");

    m_pStaffManager = pToolbarMain->addAction("用户管理");
    m_pRoleManager = pToolbarMain->addAction("角色管理");
    m_pDepartmentManager = pToolbarMain->addAction("部门管理");
    m_pJobManager = pToolbarMain->addAction("职务管理");

    m_pStaffManager->setCheckable(true);
    m_pRoleManager->setCheckable(true);
    m_pDepartmentManager->setCheckable(true);
    m_pJobManager->setCheckable(true);


    QSplitter* pMainSplitter = new QSplitter(Qt::Orientation::Horizontal);
    m_pTableView = new QTableView;
    pMainSplitter->addWidget(m_pTableView);

    QWidget * pRightWidget = new QWidget;

    QHBoxLayout * pSearchLayout = new QHBoxLayout;
    QLineEdit * pSearchKey = new QLineEdit;
    pSearchKey->setPlaceholderText("搜索内容");
    QPushButton * pBtnSearch = new QPushButton("搜索");
    pSearchLayout->addWidget(pSearchKey);
    pSearchLayout->addWidget(pBtnSearch);

    QHBoxLayout * pAddLayout = new QHBoxLayout;
    QLineEdit * pAddKey = new QLineEdit;
    pAddKey->setPlaceholderText("增加内容");
    QPushButton * pBtnAdd = new QPushButton("增加");
    pAddLayout->addWidget(pAddKey);
    pAddLayout->addWidget(pBtnAdd);

    QVBoxLayout * pRightMainLayout = new QVBoxLayout;
    pRightMainLayout->addLayout(pSearchLayout, 1);
    pRightMainLayout->addLayout(pAddLayout, 5);
    pRightMainLayout->addStretch();

    pRightWidget->setLayout(pRightMainLayout);
    pMainSplitter->addWidget(pRightWidget);

    this->setCentralWidget(pMainSplitter);

    m_pSqlQueryModel = new QSqlQueryModel(m_pTableView);
}
