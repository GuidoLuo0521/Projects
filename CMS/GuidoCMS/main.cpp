#include "mainwindow.h"
#include "logindialog.h"
#include "commonapi.h"

#include "systemmanagerdialog.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    InitGlobalParams();

    LoginDialog logindlg;
    logindlg.show();
    if(logindlg.exec() == QDialog::Accepted)
    {
        QString strStaffID = logindlg.GetUserID();
        StaffInfoSingleton::SetInstance(GetStaffInfo(strStaffID));

        SystemManagerDialog w;
        w.show();

        return a.exec();
    }
    else
        return 0;
}
