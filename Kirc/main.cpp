#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("haneda3");
    QCoreApplication::setOrganizationDomain("haneda3.com");
    QCoreApplication::setApplicationName("KIrc");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
