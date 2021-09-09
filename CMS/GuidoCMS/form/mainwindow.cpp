#include "mainwindow.h"
#include "systemmanagerdialog.h"
#include "profiledialog.h"
#include "roledatedialog.h"

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

void MainWindow::slotAccountChanged()
{
    slotShowDialog(SystemManagerDialogType);
    slotShowCurrentAccount();
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
    ProfileDialog dlg(this);

    connect( &dlg, &ProfileDialog::signalUpdateSuccess,
            m_pSystemManagerDialog, &SystemManagerDialog::slotUpdateCurrentPage);

    dlg.show();
    dlg.exec();
}

void MainWindow::slotShowDialog(MainWindow::MainWindowDialogType type)
{
    ChangeActionChecked(type);
    m_pMainStackWidget->setCurrentIndex(type);
}

void MainWindow::slotToolbarActionClicked(QAction * pAction)
{
    if(pAction == m_pActionSystemManager)
        emit signalShowCurrentDialog(SystemManagerDialogType);
    else if (pAction == m_pActionWeeklyReport)
        emit signalShowCurrentDialog(WeeklyReportDialogType);
}

void MainWindow::ChangeActionChecked(MainWindow::MainWindowDialogType type)
{
    m_pActionWeeklyReport->setChecked(false);
    m_pActionSystemManager->setChecked(false);

    switch (type) {
    case    SystemManagerDialogType: m_pActionSystemManager->setChecked(true); return;
    case    WeeklyReportDialogType: m_pActionWeeklyReport->setChecked(true); return;
    default:  return;
    }
}


void MainWindow::InitLayout()
{
    m_pMainStackWidget = new QStackedWidget;

    m_pSystemManagerDialog = new SystemManagerDialog(this);
    connect(this, &MainWindow::signalAccountChange,
            m_pSystemManagerDialog, &SystemManagerDialog::slotAccountChanged);

    m_pWeeklyReportDialog = new WeeklyReportDialog(this);
    connect(this, &MainWindow::signalAccountChange,
            m_pWeeklyReportDialog, &WeeklyReportDialog::slotAccountChanged);

    m_pMainStackWidget->addWidget(m_pSystemManagerDialog);
    m_pMainStackWidget->addWidget(m_pWeeklyReportDialog);

    InitMenuBar();
    InitToolBar();
    InitStatuBar();

    connect(this, &MainWindow::signalShowCurrentDialog, this, &MainWindow::slotShowDialog);
    connect(this, &MainWindow::signalAccountChange, this, &MainWindow::slotAccountChanged);
    this->setCentralWidget(m_pMainStackWidget);
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
   pToolBar->setAllowedAreas(Qt::ToolBarArea::LeftToolBarArea);
   this->addToolBar(Qt::ToolBarArea::LeftToolBarArea, pToolBar);   

   m_pActionSystemManager = pToolBar->addAction("系统管理");
   m_pActionWeeklyReport = pToolBar->addAction("周报管理");

   m_pActionSystemManager->setCheckable(true);
   m_pActionWeeklyReport->setCheckable(true);

   m_pActionSystemManager->setChecked(true);

   connect( pToolBar, &QToolBar::actionTriggered,
           this, &MainWindow::slotToolbarActionClicked);

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
    emit signalAccountChange();

    showMaximized();
    this->show();
}
