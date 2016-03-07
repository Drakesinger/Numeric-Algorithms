/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#include "mainwindow.h"
#include "centralwidget.h"

MWMainWindow::MWMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Lab 4 - Rare Soil");
    this->resize(800,400);
    this->MCentralWidget = new WCentralWidget(this);
    this->setCentralWidget(MCentralWidget);
}

MWMainWindow::~MWMainWindow()
{

}
