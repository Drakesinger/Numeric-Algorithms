/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#ifndef MENUDROITE_H
#define MENUDROITE_H

#include <QWidget>
// Forward declaration of classes
class QRadioButton;
class QGroupBox;

/**
 * @brief The RightMenu class
 * Contains the plot options. Allows the user to select which function to plot.
 */
class WRightMenu : public QWidget
{
    Q_OBJECT
public:
    explicit WRightMenu(QWidget *parent = 0);

signals:
    void DrawFunction1();
    void DrawFunction2();
private:
    QRadioButton* MRadioButtonFunction1;
    QRadioButton* MRadioButtonFunction2;
    QGroupBox* MGroupBoxFunctionChoice;

public slots:
    void On_Toggle_RadioButtonFunction1(bool state);
    void On_Toggle_RadioButtonFunction2(bool state);


};

#endif // MENUDROITE_H
