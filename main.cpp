#include "occQt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    occQt w;
    w.show();
    return a.exec();
}
