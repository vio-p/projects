#include "MovieAppFE.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MovieAppFE w;
    w.show();
    return a.exec();
}
