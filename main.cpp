#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Finetech GmbH");
    QCoreApplication::setOrganizationDomain("finetech.de");
    QCoreApplication::setApplicationName("FoE_GUI");

    MainWindow w;
    w.show();
    return a.exec();
}
