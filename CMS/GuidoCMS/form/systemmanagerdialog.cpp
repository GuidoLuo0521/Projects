#include "searchdialog.h"
#include "systemmanagerdialog.h"
#include "common/staffinfo.h"
#include "database/cmsdatabase.h"
#include "database/cmsdatebasedef.h"


#include "form/staffdatedialog.h"
#include "form/departmentdatedialog.h"
#include "form/jobdatedialog.h"
#include "form/roledatedialog.h"


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
#include <QMenuBar>

#include "delegate/controldelegate.h"

SystemManagerDialog::SystemManagerDialog(QWidget *parent) :
    CMSBaseWidget(parent)
{
    InitLayout();
    slotSetTableModelTableStaff();
}

SystemManagerDialog::~SystemManagerDialog()
{
}

void SystemManagerDialog::slotUpdateCurrentPage()
{
    TableDateDialog * ptableWidget = (TableDateDialog * )m_pStackedWidget->currentWidget();
    ptableWidget->slotUpdateTable(false);
}

void SystemManagerDialog::slotShowSearchDialog(bool bShow)
{
    TableDateDialog * ptableWidget = (TableDateDialog * )m_pStackedWidget->currentWidget();
    if(bShow)
        ptableWidget->getSearchDockWidget()->show();
    else
        ptableWidget->getSearchDockWidget()->hide();
}

void SystemManagerDialog::slotShowAddEntryDialog(bool bShow)
{
    TableDateDialog * ptableWidget = (TableDateDialog * )m_pStackedWidget->currentWidget();
    if(bShow)
        ptableWidget->getAddDockWidget()->show();
    else
        ptableWidget->getAddDockWidget()->hide();
}

void SystemManagerDialog::ChangeActionChecked(SystemManagerDialog::StackedWidgetType type)
{
    m_pActionStaffManager->setChecked(false);
    m_pActionRoleManager->setChecked(false);
    m_pActionDepartmentManager->setChecked(false);
    m_pActionJobManager->setChecked(false);

    switch (type) {
    //case    StaffWidget: m_pActionStaffManager->setChecked(true); return;
    case    DepartmentWidget: m_pActionDepartmentManager->setChecked(true); return;
    case    JobWidget: m_pActionJobManager->setChecked(true); return;
    case    RoleWidget: m_pActionRoleManager->setChecked(true); return;
    default: m_pActionStaffManager->setChecked(true); return;
    }
}

void SystemManagerDialog::slotSetTableModelTableStaff()
{
    ChangeActionChecked(StaffWidget);
    m_pStackedWidget->setCurrentIndex(StaffWidget);
}

void SystemManagerDialog::slotSetTableModelTableRole()
{
    ChangeActionChecked(RoleWidget);
    m_pStackedWidget->setCurrentIndex(RoleWidget);
}

void SystemManagerDialog::slotSetTableModelTableDepartment()
{
    ChangeActionChecked(DepartmentWidget);
    m_pStackedWidget->setCurrentIndex(DepartmentWidget);
}

void SystemManagerDialog::slotSetTableModelTableJob()
{
    ChangeActionChecked(JobWidget);
    m_pStackedWidget->setCurrentIndex(JobWidget);    
}

void SystemManagerDialog::InitLayout()
{
    setWindowTitle("系统管理");

    //QWidget * pMenuBar = InitMenuBar();
    QWidget * ptoolbar = InitToolBar();
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

    //this->setCentralWidget(m_pStackedWidget);

    QVBoxLayout * pMainLayout = new QVBoxLayout;
    pMainLayout->addWidget(ptoolbar);
    pMainLayout->addWidget(m_pStackedWidget);

    this->setLayout(pMainLayout);
}

QWidget *SystemManagerDialog::InitMenuBar()
{
    //QMenuBar* pMainMenuBar =  this->menuBar();
    QMenuBar* pMainMenuBar =  new QMenuBar;

    QMenu * pViewMenu = pMainMenuBar->addMenu("视图");
    m_pActionSearch = pViewMenu->addAction("搜索");
    m_pActionAddEntry = pViewMenu->addAction("增加");

    m_pActionSearch->setCheckable(true);
    m_pActionAddEntry->setCheckable(true);

    m_pActionSearch->setChecked(true);
    m_pActionAddEntry->setChecked(true);

    connect( m_pActionSearch, &QAction::triggered, this, &SystemManagerDialog::slotShowSearchDialog);
    connect( m_pActionAddEntry, &QAction::triggered, this, &SystemManagerDialog::slotShowAddEntryDialog);

    return  pMainMenuBar;
}

QWidget* SystemManagerDialog::InitToolBar()
{
    //QToolBar* pToolbarMain =  this->addToolBar("管理");
    QToolBar* pToolbarMain =  new QToolBar("管理");

    pToolbarMain->setMovable(false);
    pToolbarMain->setFloatable(false);

    m_pActionStaffManager =       pToolbarMain->addAction("用户");
    m_pActionDepartmentManager =  pToolbarMain->addAction("部门");
    m_pActionJobManager =         pToolbarMain->addAction("职务");
    m_pActionRoleManager =        pToolbarMain->addAction("角色");

    m_pActionJobManager->setCheckable(true);
    m_pActionRoleManager->setCheckable(true);
    m_pActionStaffManager->setCheckable(true);
    m_pActionDepartmentManager->setCheckable(true);

    connect( m_pActionJobManager, &QAction::triggered, this, &SystemManagerDialog::slotSetTableModelTableJob);
    connect( m_pActionRoleManager, &QAction::triggered, this, &SystemManagerDialog::slotSetTableModelTableRole);
    connect( m_pActionStaffManager, &QAction::triggered, this, &SystemManagerDialog::slotSetTableModelTableStaff);
    connect( m_pActionDepartmentManager, &QAction::triggered, this, &SystemManagerDialog::slotSetTableModelTableDepartment);

    return  pToolbarMain;
}


QWidget* SystemManagerDialog::InitTableInfoManagerStaff()
{
    return  new StaffDateDialog;
}
QWidget* SystemManagerDialog::InitTableInfoManagerDepartment()
{
    return  new DepartmentDateDialog;
}
QWidget* SystemManagerDialog::InitTableInfoManagerRole()
{
    return  new RoleDateDialog;
}
QWidget* SystemManagerDialog::InitTableInfoManagerJob()
{
    return  new JobDateDialog;
}


