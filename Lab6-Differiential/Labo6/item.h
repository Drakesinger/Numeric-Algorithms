/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#ifndef ITEM_H
#define ITEM_H

#include "pendulum.h"
#include "euler.h"
#include "rk.h"

#include <QGraphicsItem>

class Item : public QGraphicsItem
{
public:
    Item();
    ~Item();

    void start();
    void stop();

    OneNode& upper();
    OneNode& lower();

    const TwoNodes *pendulum();

    QString solver();
    void setSolver(const QString& solver);

    double dt();
    void setDt(double dt);

    double g();
    void setG(double g);

    QColor upperColor();
    void setUpperColor(const QColor& colour);

    QColor lowerColor();
    void setLowerColor(const QColor& colour);

    int opacity();
    void setOpacity(int opacity);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void drawIcon(QPainter *painter, const QRect &rect);

    void updateScale(double newScale);
    void updateTime(double newTime);

private:
    TwoNodes *m_pendulum;

    QString m_solver;
    double m_dt;
    double m_g;

    double m_scale;

    /**
     * Initial states of the upper and lower pendulums.
     */
    OneNode m_upper, m_lower;

    QColor m_upperColor;
    QColor m_lowerColor;
    int m_opacity;
};

#endif // ITEM_H
