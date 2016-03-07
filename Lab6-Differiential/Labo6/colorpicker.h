/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <QToolButton>

class ColorPicker : public QToolButton
{
    Q_OBJECT

public:
    ColorPicker(QWidget *parent);

    QColor color();
    void setColor(const QColor& color);

signals:
    void colorChanged(const QColor& color);

protected slots:
    void selfClicked();

protected:
    void paintEvent(QPaintEvent *event);

    QColor m_color;
};

#endif // COLORPICKER_H
