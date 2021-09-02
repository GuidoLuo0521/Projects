#include "common/commonapi.h"

#include "form/logindialog.h"
#include "form/systemmanagerdialog.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitGlobalParams();

    LoginDialog logindlg;
    SystemManagerDialog sysMgrDlg;

    //点击登录对话框的登录按钮; 进入主界面
    QObject::connect(&logindlg, SIGNAL(signalShowMainWindow()), &sysMgrDlg, SLOT(slotShowWindow()));
    //点击主界面的注销; 返回登录对话框
    QObject::connect(&sysMgrDlg, SIGNAL(signalExitCurrentAccount()), &logindlg, SLOT(slotShowMainWindow()));

    logindlg.show();

    return a.exec();

}
