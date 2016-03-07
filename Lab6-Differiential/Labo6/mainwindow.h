/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "item.h"

class QLabel;
namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    Item *activeItem();

    void resetStatusBar();

    static QPair<QColor, QColor> randNodeColor();

protected slots:
    void addPendulum();
    void removePendulum();
    void changePendulum(int index);

    void startSim();
    void pauseSim();
    void stopSim();

    void zoomIn();
    void zoomOut();
    void zoomBestFit();

    void useOpenGL(bool on);

    void updatePendulum();

    void updateNodeColors();

    void updateStatusBar();

    void setDefaults();

private:
    Ui::MainWindowClass *ui;

    QTimer *m_statusBarTimer;
    QLabel *m_statusBarTime;

    int m_pendulumCount;
    bool m_maskUpdates;
};

#endif // MAINWINDOW_H
