#include "qtsim.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtSim w;
    w.setWindowTitle("Foo");
    w.showMaximized();
    return a.exec();
}
