/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
