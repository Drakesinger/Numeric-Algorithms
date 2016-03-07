/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#include "iteminfo.h"

#include <QApplication>
#include <QFontMetrics>
#include <QPainter>
#include <QTextOption>

#include <cmath>

ItemInfo::ItemInfo()
    : m_iconSize(16.0)
    , m_horizontalPadding(10.0)
    , m_verticalPadding(5.0)
{
}

ItemInfo::~ItemInfo()
{
}

QRectF ItemInfo::boundingRect() const
{
    // The widest part is the title text, so use that for the bounding width
    QFont f = QApplication::font();
    f.setBold(true);
    const double tw = QFontMetricsF(f).width("Mechanical Energy");

    return QRectF(0.0, 0.0,
                  2 * m_horizontalPadding + tw,
                  2 * m_verticalPadding + 20.0 + m_pendula.count() * (m_iconSize + 3.0));
}

void ItemInfo::paint(QPainter *painter,
                                   const QStyleOptionGraphicsItem *,
                                   QWidget *)
{
    // Draw the bounding rectangle
    QLinearGradient grad(QPoint(0, 0), QPoint(0, 60));
    grad.setColorAt(0, QColor(40, 40, 40, 100));
    grad.setColorAt(0.8, QColor(40, 40, 40, 30));

    painter->setPen(QPen(Qt::black, 0.8));
    painter->setBrush(grad);
    painter->drawRoundedRect(boundingRect(), 5.0, 5.0);

    // Draw the title text ("Mechanical Energy"), bold with a slight shadow
    painter->save();
    QRectF r = boundingRect().adjusted(m_horizontalPadding, m_verticalPadding,
                                       -m_horizontalPadding, 0);
    QFont f = QApplication::font();
    f.setBold(true);
    painter->setFont(f);

    painter->setPen(QColor(255, 255, 255, 180));
    painter->drawText(r, Qt::AlignHCenter, "Mechanical Energy");
    painter->translate(0.0, -1.0);
    painter->setPen(Qt::black);
    painter->drawText(r, Qt::AlignHCenter, "Mechanical Energy");
    painter->restore();

    // Translate to make painting easier
    painter->translate(m_horizontalPadding, m_verticalPadding + 20.0);

    // Use the worst case width as that of the first tab stop
    QTextOption to;
    to.setTabStop(QApplication::fontMetrics().width("-00.0J "));

    // Draw the individual pendulum energy
    foreach (Item *item, m_pendula)
    {
        // First draw the icon
        item->drawIcon(painter, QRect(0, 0, m_iconSize, m_iconSize));

        // Next comes the text
        const double currE= item->pendulum()->energy();
        const double initE = item->pendulum()->initEnergy();
        const double change = (currE - initE) / initE * 100.0;

        QString text = QString("%1J\t(%2%3%)").arg(currE, 2, 'f', 1)
                                              .arg(change > 0.0 ? '+' : '-')
                                              .arg(fabs(change), 3, 'f', 1);

        painter->save();
        painter->translate(m_iconSize + 7.0, 0.0);
        painter->drawText(QRectF(0.0, 0.0, r.width() - m_iconSize - 7.0, r.height()),
                          text, to);
        painter->restore();

        // Finally translate down a few units
        painter->translate(0.0, m_iconSize + 3.0);
    }
}

void ItemInfo::setPendula(const QMap<QString, Item *> &pendula)
{
    const int count = m_pendula.count();

    m_pendula = pendula;

    // If the number of pendulums has changed then so has our bounding rect
    if (count != m_pendula.count())
    {
        prepareGeometryChange();
    }
}
