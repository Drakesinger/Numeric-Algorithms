/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#include "widget.h"
#include "item.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QMap>

Widget::Widget(QWidget *parent)
    : QGraphicsView(parent)
    , m_scale(10.0)
    , m_simUpdateFreq(1000 / 100)
    , m_isPaused(false)
    , m_info(new ItemInfo)
{
    // Create a scene to store the pendulums
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setScene(scene);

    // Hide the info item and add it to the scene on top of the pendula
    m_info->hide();
    m_info->setZValue(1.0);
    scene->addItem(m_info);

    // Create a timer to update the simulation
    m_simTimer = new QTimer(this);
    connect(m_simTimer, SIGNAL(timeout()), this, SLOT(advanceSimulation()));

    // Init the last update time
    m_lastUpdate.start();
}

Widget::~Widget()
{
    delete m_info;
}

void Widget::addPendulum(const QString &name, Item *pendulum)
{
    scene()->addItem(pendulum);
    pendulum->setPos(0.0, 0.0);
    pendulum->updateScale(m_pScaleFactor);

    m_pendula[name] = pendulum;
}

void Widget::removePendulum(const QString &name)
{
    //Note : graphics framwork delete the object for us
    scene()->removeItem(m_pendula[name]);

    m_pendula.remove(name);
}

QMap<QString, Item *> Widget::pendula()
{
    return m_pendula;
}

void Widget::startSim()
{
    // Reset the simulation and actual times
    m_simTime = 0.0;
    m_lastUpdate.restart();

    // Start of all of the pendulums
    foreach (Item *pendulum, m_pendula)
    {
        pendulum->start();
    }

    // Update the info box with the current set of pendulums
    m_info->setPendula(m_pendula);
    m_info->show();

    // Start the timers
    m_simTimer->start(m_simUpdateFreq);
}

void Widget::pauseSim()
{
    // If we are not paused, pause ourself
    if (!m_isPaused)
    {
        m_isPaused = true;

        // Stop the timers
        m_simTimer->stop();
    }
    // If we are paused, unpause ourself
    else
    {
        m_isPaused = false;

        // Restart the timers
        m_simTimer->start(m_simUpdateFreq);
        // Reset the last update time
        m_lastUpdate.restart();
    }
}

void Widget::stopSim()
{
    // Stop the timers
    m_simTimer->stop();

    // Stop all of the pendulums
    foreach (Item *pendulum, m_pendula)
    {
        pendulum->stop();
    }

    // We are not paused
    m_isPaused = false;

    // Hide the info box as it is meaningless when the simulation is stopped
    m_info->hide();

    // Request a repaint to clear ourself
    scene()->update();
}

double Widget::time()
{
    return m_simTime;
}

double Widget::pendulumScaleFactor()
{
    return m_pScaleFactor;
}

double Widget::scaleFactor()
{
    return m_scale;
}

void Widget::setScaleFactor(double sf)
{
    // Update the scale
    m_scale = sf;

    // Compute the new pendulum scale factor
    m_pScaleFactor = qMin(sceneRect().width(), sceneRect().height()) / m_scale;

    foreach (Item *pendulum, m_pendula)
    {
        pendulum->updateScale(m_pScaleFactor);
    }

    // Update the scene to force all of the pendula to redraw themselves
    update();
}

double Widget::idealScaleFactor()
{
    double largestPendulm = 0;

    // Loop over each pendulum looking for the largest
    foreach (Item *pendulum, m_pendula)
    {
        // Get the bounds of the pendulum
        QRectF bounds = pendulum->boundingRect();

        // Get its unscale size; height() would also work here
        double pendulumSize = bounds.width() / pendulumScaleFactor();

        largestPendulm = qMax(pendulumSize, largestPendulm);
    }

    // Subtract a bit to account for the node on the end - magic number alert
    largestPendulm -= 0.2;

    return largestPendulm;
}

void Widget::advanceSimulation()
{
    // Advance the simulation forward by the amount of time that has passed
    m_simTime += m_lastUpdate.elapsed();

    // Reset the last update time
    m_lastUpdate.restart();

    // Update the scene
    foreach (Item *pendulum, m_pendula)
    {
        pendulum->updateTime(m_simTime);
    }

    m_info->update();
}

void Widget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    // Make the scene ever so slightly smaller than the view
    QRectF newSceneRect(-width() / 2.0, -height() / 2.0, width(), height());
    newSceneRect.adjust(0.0, 0.0, -5.0, -5.0);

    // Ensure the range of the smaller axis is between 0..m_scale
    m_pScaleFactor = qMin(newSceneRect.width(), newSceneRect.height()) / m_scale;

    foreach (Item *pendulum, m_pendula)
    {
        pendulum->updateScale(m_pScaleFactor);
    }

    // Update the scene rect
    setSceneRect(newSceneRect);

    // Keep the info box in the top left of the scene
    m_info->setPos(sceneRect().topLeft() + QPointF(20.0, 20.0));
}
