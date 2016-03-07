/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#include "item.h"

#include <QtDebug>
#include <QPainter>
#include <QColor>

#include <cmath>

Item::Item()
    : m_pendulum(0)
{
}

Item::~Item()
{
    if (m_pendulum)
    {
        stop();
    }
}

void Item::start()
{
    // Create the actual pendulum object
    if (m_solver == "Euler")
    {
        m_pendulum = new Euler(upper(), lower(), m_dt, m_g);
    }
    else if (m_solver == "Runge Kutta")
    {
        m_pendulum = new RK(upper(), lower(), m_dt, m_g);
    }
}

void Item::stop()
{
    delete m_pendulum;
    m_pendulum = 0;
}

const TwoNodes *Item::pendulum()
{
    return m_pendulum;
}

OneNode& Item::upper()
{
    return m_upper;
}

OneNode& Item::lower()
{
    return m_lower;
}

QString Item::solver()
{
    return m_solver;
}

void Item::setSolver(const QString& solver)
{
    m_solver = solver;
}

double Item::dt()
{
    return m_dt;
}

void Item::setDt(double dt)
{
    m_dt = dt;
}

double Item::g()
{
    return m_g;
}

void Item::setG(double g)
{
    m_g = g;
}

QColor Item::upperColor()
{
    return m_upperColor;
}

void Item::setUpperColor(const QColor& color)
{
    m_upperColor = color;
}

QColor Item::lowerColor()
{
    return m_lowerColor;
}

void Item::setLowerColor(const QColor& color)
{
    m_lowerColor = color;
}

int Item::opacity()
{
    return m_opacity;
}

void Item::setOpacity(int opacity)
{
    m_opacity = opacity;
}

QRectF Item::boundingRect() const
{
    if (!m_pendulum)
    {
        return QRectF(0.0, 0.0, 0.0, 0.0);
    }
    else
    {
        const double max = (m_pendulum->l1() + m_pendulum->l2() + 0.2)
                          * m_scale;

        return QRectF(QPointF(-max, -max), QPointF(max, max));
    }
}

void Item::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *,
                               QWidget *)
{
    // Only paint if the pendulum is running
    if (!m_pendulum)
    {
        return;
    }

    // Various drawing sizes
    const double nodeSize = 0.2 * m_scale;
    const double lineSize = 0.04 * m_scale;

    // Scaled location of the upper node
    const QPointF upperNode = QPointF(m_pendulum->l1() * sin(m_pendulum->theta1()),
                                     m_pendulum->l1() * cos(m_pendulum->theta1()))
                           * m_scale;

    // Scaled location of the lower node
    const QPointF lowerNode = QPointF(m_pendulum->l2() * sin(m_pendulum->theta2()),
                                     m_pendulum->l2() * cos(m_pendulum->theta2()))
                           * m_scale + upperNode;

    // Amount of material to omit from the end of the first connecting line
    const QPointF upperCut = QPointF(sin(m_pendulum->theta1()),
                                     cos(m_pendulum->theta1())) * nodeSize;

    // Amount of material to omit from both ends of the second line
    const QPointF lowerCut = QPointF(sin(m_pendulum->theta2()),
                                     cos(m_pendulum->theta2())) * nodeSize;

    painter->setOpacity(m_opacity / 100.0);

    // First come the connecting lines
    painter->setPen(QPen(Qt::black, lineSize, Qt::SolidLine, Qt::RoundCap));

    QLineF connectingLines[] =
    {
        QLineF(QPointF(0.0, 0.0), upperNode - upperCut),
        QLineF(upperNode + lowerCut, lowerNode - lowerCut)
    };

    painter->drawLines(connectingLines, 2);
    painter->setPen(Qt::NoPen);

    // Next comes the upper node
    painter->setBrush(m_upperColor);
    painter->drawEllipse(upperNode, nodeSize, nodeSize);

    // Finally the lower node
    painter->setBrush(m_lowerColor);
    painter->drawEllipse(lowerNode, nodeSize, nodeSize);
}

void Item::drawIcon(QPainter *painter, const QRect &rect)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing, false);

    QPolygon triangle;
    triangle << rect.topLeft() << rect.bottomLeft() << rect.topRight();
    painter->setBrush(m_upperColor);
    painter->drawPolygon(triangle);

    triangle[0] = rect.bottomRight();
    painter->setBrush(m_lowerColor);
    painter->drawPolygon(triangle);

    painter->setPen(Qt::gray);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect.adjusted(0, 0, -1, -1));

    painter->restore();
}

void Item::updateScale(double newScale)
{
    m_scale = newScale;

    // Recompute our bounding box
    prepareGeometryChange();
}

void Item::updateTime(double newTime)
{
    // Actual time (s as opposed to ms)
    double actualTime = newTime / 1000.0;

    // Update the pendulum
    if (actualTime > m_pendulum->time())
    {
        m_pendulum->update(actualTime);
    }

    prepareGeometryChange();
}
