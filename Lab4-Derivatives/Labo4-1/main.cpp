/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MWMainWindow w;
    w.show();

    return a.exec();
}
