/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#pragma once

#include <QWidget>
class QScrollArea;
class Graph;
class WRightMenu;

/**
 * @brief The WCentralWidget class
 * Contains the graph area and the right menu that gives choices to the user.
 */
class WCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WCentralWidget(QWidget *parent = 0);

signals:

public slots:
    void DrawFunction1();
    void DrawFunction2();
private:
    Graph* MGraph;
    WRightMenu* MRightMenu;

    // The whole project revolves around these functions:
    double static Function1(double x);
    double static Function2(double x);

    double Derivative(double x, double(*f)(double));
    double SecondDerivative(double x, double(*f)(double));
};
