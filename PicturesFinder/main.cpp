#include "picturesfinder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PicturesFinder w;
    w.show();

    return a.exec();
}
