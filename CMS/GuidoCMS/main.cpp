#include "common/commonapi.h"

#include "form/logindialog.h"
#include "form/systemmanagerdialog.h"

#include <QApplication>

#include <form/mainwindow.h>
#include <form/staffpassworddialog.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitGlobalParams();

#if 1
    LoginDialog logindlg;
    MainWindow maindlg;
    //SystemManagerDialog maindlg;

    //点击登录对话框的登录按钮; 进入主界面
    QObject::connect(&logindlg, SIGNAL(signalShowMainWindow()), &maindlg, SLOT(slotShowWindow()));
    //点击主界面的注销; 返回登录对话框
    QObject::connect(&maindlg, SIGNAL(signalExitCurrentAccount()), &logindlg, SLOT(slotShowMainWindow()));

    logindlg.show();

#elif 0
    SystemManagerDialog  pManager;
    pManager.show();
#elif 0
    StaffInfoSingleton::SetInstance(GetStaffInfo("000002", "000002"));
    StaffPasswordDialog w;
    w.show();
#endif




    return a.exec();

}
