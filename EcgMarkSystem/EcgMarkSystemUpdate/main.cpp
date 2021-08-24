#include "autoupdatewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AutoUpdateWidget w;
    w.show();

    return a.exec();
}
