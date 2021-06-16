#include <QCoreApplication>

#include "GeneralImageTransforms.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Resize();

//    PyrDown();

    //BuildPyramid();

    PyrUp();

    return a.exec();
}
