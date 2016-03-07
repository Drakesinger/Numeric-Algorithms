/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QTime>

#include "item.h"
#include "iteminfo.h"

class Widget : public QGraphicsView
{
    Q_OBJECT

public:
    Widget(QWidget *parent);
    ~Widget();

    void addPendulum(const QString &name, Item *pendulum);
    void removePendulum(const QString &name);
    QMap<QString, Item *> pendula();

    void startSim();
    void pauseSim();
    void stopSim();

    double time();

    double pendulumScaleFactor();

    double scaleFactor();
    void setScaleFactor(double sf);
    double idealScaleFactor();

protected slots:
    void advanceSimulation();
    void resizeEvent(QResizeEvent *event);

private:
    double m_pScaleFactor;
    double m_scale;

    const int m_simUpdateFreq;

    QTimer *m_simTimer;
    double m_simTime;
    QTime m_lastUpdate;

    bool m_isPaused;

    QMap<QString, Item *> m_pendula;

    ItemInfo *m_info;
};

#endif // WIDGET_H
