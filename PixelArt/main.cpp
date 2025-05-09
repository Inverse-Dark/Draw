#include "PixelArt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PixelArt w;
    w.show();
    return a.exec();
}
