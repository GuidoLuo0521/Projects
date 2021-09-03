#include "mainwindow.h"
#include "systemmanagerdialog.h"
#include "staffpassworddialog.h"
#include "tablerolemanagerdialog.h"

#include <QStatusBar>
#include <QTimer>
#include <QToolBar>

#include <common/staffinfo.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    InitLayout();
}

MainWindow::~MainWindow()
{

}

void MainWindow::slotUpdateTime()
{
    //[1] 获取时间
    QDateTime current_time = QDateTime::currentDateTime();
    QString timestr = current_time.toString( "yyyy-MM-dd hh:mm:ss"); //设置显示的格式
    m_pStatuTimeLabel->setText(timestr); //设置label的文本内容为时间
}

void MainWindow::slotShowCurrentAccount()
{
    CStaffInfo * pStaffInfo = StaffInfoSingleton::GetInstance();
    QString str = QString("%1 %2")
                      .arg(pStaffInfo->GetDepartment())
                      .arg(pStaffInfo->GetStaffName());

    m_pStatuAccountLabel->setText("当前登录人员：" + str);
    this->setWindowTitle("GuidoCMS - " + str);
}

void MainWindow::slotUpdateStaffPassword()
{
    StaffPasswordDialog dlg(this);

    connect( &dlg, &StaffPasswordDialog::signalUpdateSuccess,
            m_pSystemManagerDialog, &SystemManagerDialog::slotUpdateCurrentPage);

    dlg.show();
    dlg.exec();
}

void MainWindow::InitLayout()
{
    m_pStackCentralWidget = new QStackedWidget;

    m_pSystemManagerDialog = new SystemManagerDialog(this);
    //this->setCentralWidget(m_pSystemManagerDialog);

    m_pStackCentralWidget->addWidget(m_pSystemManagerDialog);

    InitMenuBar();
    InitToolBar();
    InitStatuBar();

    this->setCentralWidget(m_pStackCentralWidget);
}

QWidget *MainWindow::InitMenuBar()
{
    QMenuBar * pMenuBar = this->menuBar();
    QMenu * pMenuAccount = pMenuBar->addMenu("账户");

    m_pActionExit = pMenuAccount->addAction("退出账户");
    m_pActionUPW = pMenuAccount->addAction("更新密码");

    connect( m_pActionExit, &QAction::triggered, this, &MainWindow::slotExitLogin);
    connect( m_pActionUPW, &QAction::triggered, this, &MainWindow::slotUpdateStaffPassword);

    return  pMenuBar;
}

QWidget *MainWindow::InitToolBar()
{
   QToolBar * pToolBar = new QToolBar("窗口");
   pToolBar->setMovable(false);
   this->addToolBar(Qt::ToolBarArea::LeftToolBarArea, pToolBar);

   pToolBar->setAllowedAreas(Qt::ToolBarArea::LeftToolBarArea);

   QAction * pActionSystemManager = pToolBar->addAction("系统管理");
   pActionSystemManager->setCheckable(true);
   pActionSystemManager->setChecked(true);

   connect(pActionSystemManager, &QAction::triggered,
           m_pSystemManagerDialog, &SystemManagerDialog::slotSetShow);

   return  pToolBar;
}

QWidget *MainWindow::InitStatuBar()
{
    QStatusBar * pStatubar = this->statusBar();
    m_pStatuTimeLabel = new QLabel(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    pStatubar->addPermanentWidget(m_pStatuTimeLabel);

    QTimer * pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, &QTimer::timeout, this, &MainWindow::slotUpdateTime);
    pTimer->start();

    m_pStatuAccountLabel = new QLabel("当前登录人员：");
    pStatubar->addWidget(m_pStatuAccountLabel);

    return pStatubar;
}

void MainWindow::slotExitLogin()
{
    emit signalExitCurrentAccount();
    close();
}

void MainWindow::slotShowWindow()
{
    slotShowCurrentAccount();
    showMaximized();
    this->show();
}
