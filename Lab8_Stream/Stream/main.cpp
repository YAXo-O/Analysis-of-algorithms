#include "streamwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StreamWindow w;
    w.show();

    return a.exec();
}
