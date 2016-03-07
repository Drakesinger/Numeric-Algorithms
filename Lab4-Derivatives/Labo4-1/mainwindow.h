/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class WCentralWidget;
class MWMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MWMainWindow(QWidget *parent = 0);
    ~MWMainWindow();

private:
    WCentralWidget* MCentralWidget;
};

#endif // MAINWINDOW_H

