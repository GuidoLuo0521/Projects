#include <QCoreApplication>

#include "GeneralImageTransforms.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Resize();

//    PyrDown();

    //BuildPyramid();

    //PyrUp();

    WarpAffine();

    return a.exec();
}
