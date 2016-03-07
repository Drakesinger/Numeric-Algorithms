/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <QGraphicsItem>

#include "item.h"

class ItemInfo : public QGraphicsItem
{
public:
    ItemInfo();
    ~ItemInfo();

    void setPendula(const QMap<QString, Item *> &pendula);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    const double m_iconSize;
    const double m_horizontalPadding;
    const double m_verticalPadding;

    QMap<QString, Item *> m_pendula;
};

#endif // ITEMINFO_H
