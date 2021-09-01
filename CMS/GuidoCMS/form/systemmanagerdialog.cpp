#include "searchdialog.h"
#include "systemmanagerdialog.h"
#include "common/staffinfo.h"
#include "database/cmsdatabase.h"
#include "database/cmsdatebasedef.h"


#include "form/tablestaffmanagerdialog.h"
#include "form/tabledepartmentmanagerdialog.h"
#include "form/tablejobmanagerdialog.h"
#include "form/tablerolemanagerdialog.h"


#include <QToolBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QStandardItemModel>
#include <QStackedWidget>
#include <QTimer>
#include <QDockWidget>
#include <QStatusBar>

#include "delegate/controldelegate.h"

SystemManagerDialog::SystemManagerDialog(QWidget *parent) :
    QMainWindow(parent)
{
    InitLayout();

    slotTableChange();
}

SystemManagerDialog::~SystemManagerDialog()
{
}

void SystemManagerDialog::slotTableChange()
{
    QAction * pAction = (QAction*)sender();

    if(pAction == m_pJobManager)
        SetTableModelTableJob();
    else if(pAction == m_pRoleManager)
        SetTableModelTableRole();
    else if(pAction == m_pDepartmentManager)
        SetTableModelTableDepartment();
    else
        SetTableModelTableStaff();

    ActionChecked(pAction);
}

void SystemManagerDialog::slotUpdateTime()
{
    //[1] 获取时间
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString( "yyyy-MM-dd hh:mm:ss"); //设置显示的格式
    m_pStatuTimeLabel->setText(timestr); //设置label的文本内容为时间
}

void SystemManagerDialog::slotExitLogin()
{
    emit signalExitCurrentAccount(); close();
}

void SystemManagerDialog::slotShowWindow()
{
    CStaffInfo * pStaffInfo = StaffInfoSingleton::GetInstance();
    QString str = QString("当前登录人员：%1 %2 %3")
                      .arg(pStaffInfo->GetDepartment())
                      .arg(pStaffInfo->GetStaffID())
                      .arg(pStaffInfo->GetStaffName());

    m_pStatuAccountLabel->setText(str);
    this->show();
}

void SystemManagerDialog::ActionChecked(QAction * pAction)
{
    m_pStaffManager->setChecked(false);
    m_pRoleManager->setChecked(false);
    m_pDepartmentManager->setChecked(false);
    m_pJobManager->setChecked(false);

    if(pAction == nullptr)
        pAction = m_pStaffManager;

    pAction->setChecked(true);
}

void SystemManagerDialog::SetTableModelTableStaff()
{
    m_pStackedWidget->setCurrentIndex(StaffWidget);
}

void SystemManagerDialog::SetTableModelTableRole()
{
    m_pStackedWidget->setCurrentIndex(RoleWidget);
}

void SystemManagerDialog::SetTableModelTableDepartment()
{    
    m_pStackedWidget->setCurrentIndex(DepartmentWidget);
}

void SystemManagerDialog::SetTableModelTableJob()
{
    m_pStackedWidget->setCurrentIndex(JobWidget);    
}

void SystemManagerDialog::InitLayout()
{
    setWindowTitle("系统管理");

    QWidget * ptoolbar = InitToolBar();
    QWidget * pstatubar = InitStatuBar();
    QWidget * ptableviewStaff = InitTableInfoManagerStaff();
    QWidget * ptableviewDepartment = InitTableInfoManagerDepartment();
    QWidget * ptableviewRole = InitTableInfoManagerRole();
    QWidget * ptableviewJob = InitTableInfoManagerJob();
    //QWidget * psearchview =InitSearchView();

    //
    m_pStackedWidget = new QStackedWidget;
    m_pStackedWidget->addWidget(ptableviewStaff);
    m_pStackedWidget->addWidget(ptableviewDepartment);
    m_pStackedWidget->addWidget(ptableviewJob);
    m_pStackedWidget->addWidget(ptableviewRole);

    this->setCentralWidget(m_pStackedWidget);
}

QWidget* SystemManagerDialog::InitToolBar()
{
    QToolBar* pToolbarMain =  this->addToolBar("管理");
    pToolbarMain->setMovable(false);
    pToolbarMain->setFloatable(false);

    m_pStaffManager =       pToolbarMain->addAction("用户");
    m_pDepartmentManager =  pToolbarMain->addAction("部门");
    m_pJobManager =         pToolbarMain->addAction("职务");
    m_pRoleManager =        pToolbarMain->addAction("角色");

    //2011-11-23-QTooBar中最右一个图标的靠右对齐方式
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //toolBar is a pointer to an existing toolbar
    pToolbarMain->addWidget(spacer);
    pToolbarMain->setFloatable(false);
    m_pExit =  pToolbarMain->addAction("退出登录");

    m_pJobManager->setCheckable(true);
    m_pRoleManager->setCheckable(true);
    m_pStaffManager->setCheckable(true);    
    m_pDepartmentManager->setCheckable(true);

    connect( m_pJobManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pRoleManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pStaffManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);
    connect( m_pDepartmentManager, &QAction::triggered, this, &SystemManagerDialog::slotTableChange);

    connect( m_pExit, &QAction::triggered, this, &SystemManagerDialog::slotExitLogin);

    return  pToolbarMain;
}

QWidget *SystemManagerDialog::InitStatuBar()
{
    QStatusBar * pStatubar = this->statusBar();
    m_pStatuTimeLabel = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    pStatubar->addPermanentWidget(m_pStatuTimeLabel);

    QTimer * pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, &QTimer::timeout, this, &SystemManagerDialog::slotUpdateTime);
    pTimer->start();

    m_pStatuAccountLabel = new QLabel("当前登录人员：");
    pStatubar->addWidget(m_pStatuAccountLabel);

    return pStatubar;

}
QWidget* SystemManagerDialog::InitTableInfoManagerStaff()
{
    return  new TableStaffManagerDialog(this);
}
QWidget* SystemManagerDialog::InitTableInfoManagerDepartment()
{
    return  new TableDepartmentManagerDialog(this);
}
QWidget* SystemManagerDialog::InitTableInfoManagerRole()
{
    return  new TableRoleManagerDialog(this);
}
QWidget* SystemManagerDialog::InitTableInfoManagerJob()
{
    return  new TableJobManagerDialog(this);
}


