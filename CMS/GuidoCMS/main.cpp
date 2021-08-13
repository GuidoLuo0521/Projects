#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog logindlg;
    logindlg.show();

    if(logindlg.exec() == QDialog::Accepted)
    {
        MainWindow w;
        w.show();

        return a.exec();
    }
    else
        return 0;
}
