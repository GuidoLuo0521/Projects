#include "autoupdatewidget.h"

#include <Windows.h>
#include <QApplication>

#include "GenPdbFile.h"

int main(int argc, char *argv[])
{

#ifdef Q_OS_WIN
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
#endif

    QApplication a(argc, argv);

    AutoUpdateWidget w;
    w.show();

    return a.exec();
}
