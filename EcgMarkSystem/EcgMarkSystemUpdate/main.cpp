#include "mainwindow.h"
#include "autoupdatewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    AutoUpdateWidget w;
    w.show();
    return a.exec();
}
