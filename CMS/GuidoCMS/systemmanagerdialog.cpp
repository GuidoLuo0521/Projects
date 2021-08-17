#include "systemmanagerdialog.h"
#include "ui_systemmanagerdialog.h"

#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>

#include <QStandardItemModel>

SystemManagerDialog::SystemManagerDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemManagerDialog)
{
    ui->setupUi(this);

    InitLayout();
}

SystemManagerDialog::~SystemManagerDialog()
{
    delete ui;
}

void SystemManagerDialog::InitLayout()
{
    QToolBar* pToolbarMain =  this->addToolBar("管理");

    m_pStaffManager = pToolbarMain->addAction("用户管理");


    m_pRoleManager = pToolbarMain->addAction("角色管理");
    m_pDepartmentManager = pToolbarMain->addAction("部门管理");
    m_pJobManager = pToolbarMain->addAction("职务管理");

    QSplitter* pMainSplitter = new QSplitter(Qt::Orientation::Vertical);
    QTableView * pTableView = new QTableView;
    pMainSplitter->addWidget(pTableView);

    QSplitter* pRightSplitter = new QSplitter(pMainSplitter);

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

    pRightSplitter->setLayout(pRightMainLayout);

    this->setCentralWidget(pMainSplitter);

}
