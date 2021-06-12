#include <QCoreApplication>

#include "IntroductionToOpenCV.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


#if 0
    {
        const char* szPath = "../lena.jpg";
        DisplayPicture(szPath);
    }
#endif


#if 1
    {
        const char* szPath = "../test.mp4";
        PlayVideo(szPath);
    }
#endif


    return a.exec();
}
