/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#include "colorpicker.h"

#include <QMouseEvent>

#include <QPixmap>
#include <QPainter>
#include <QColorDialog>

ColorPicker::ColorPicker(QWidget *parent)
    : QToolButton(parent)
{
    setColor(Qt::blue);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    connect(this, SIGNAL(clicked()), this, SLOT(selfClicked()));
}

QColor ColorPicker::color()
{
    return m_color;
}

void ColorPicker::setColor(const QColor& color)
{
    m_color = color;

    // Request a redraw
    update();
}

void ColorPicker::paintEvent(QPaintEvent *event)
{
    QToolButton::paintEvent(event);

    QPainter p(this);

    // Compute the dimensions of the rectangle to paint to
    const int corr = 5;
    QRect r = rect().adjusted(corr, corr, -corr - 1, -corr - 1);

    p.setBrush(m_color);
    p.setPen(Qt::lightGray);
    p.drawRect(r);
}

void ColorPicker::selfClicked()
{
    // Ask the user to pick a colour
    QColor c = QColorDialog::getColor(m_color, this);

    // As long as it is valid, use it
    if (c.isValid())
    {
        setColor(c);
        emit colorChanged(c);
    }
}
