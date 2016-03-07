/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#include <QtMath>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStandardItemModel>
#include <QLayout>
#include <QtWidgets>
#include <QDebug>


#include "centralwidget.h"
#include "graph.h"
#include "rightmenu.h"


// Definitions
#define H 0.001
#define PACE 1
#define MAXIMUM_RANGE 15

WCentralWidget::WCentralWidget(QWidget *parent) : QWidget(parent)
{
    // Instantiate the graph area and the right menu.
    MGraph = new Graph(this);
    MRightMenu = new WRightMenu(this);

    // Create a layout and add the components.
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(MGraph);
    layout->addWidget(MRightMenu);

    // Draw function1 by default.
    DrawFunction1();
}

void WCentralWidget::DrawFunction1()
{
    MGraph->clearPlottables();
    QCPDataMap *dataGraph = new QCPDataMap();

    //Function 1
    for(double i = 0;i<MAXIMUM_RANGE;i+=PACE)
    {
        dataGraph->insert(i,QCPData(i,Function1(i)));
    }
    MGraph->addPlot(dataGraph,"f1(x)");

    //The derivative of function 1
    dataGraph = new QCPDataMap();
    for(double i = 0;i<MAXIMUM_RANGE;i+=PACE)
    {
        dataGraph->insert(i,QCPData(i,Derivative(i,&Function1)));
    }
    MGraph->addPlot(dataGraph,"f1'(x)");

    //The second derivative of function 1
    dataGraph = new QCPDataMap();
    for(double i = 0;i<MAXIMUM_RANGE;i+=PACE)
    {
        dataGraph->insert(i,QCPData(i,SecondDerivative(i,&Function1)));
    }
    MGraph->addPlot(dataGraph,"f1''(x)");
}

void WCentralWidget::DrawFunction2()
{
    MGraph->clearPlottables();
    //Function 2
    QCPDataMap *dataGraph = new QCPDataMap();
    for(double i = 0;i<MAXIMUM_RANGE;i+=PACE)
    {
        if(i!=1)
        {
            dataGraph->insert(i,QCPData(i,Function2(i)));
        }
    }
    MGraph->addPlot(dataGraph,"f2(x)");

    //The second derivative of function 2
    dataGraph = new QCPDataMap();
    for(double i = 0;i<MAXIMUM_RANGE;i+=PACE)
    {
        if(i!=1)
        {
            dataGraph->insert(i,QCPData(i,Derivative(i,&Function2)));
        }
    }
    MGraph->addPlot(dataGraph,"f2'(x)");

    //The second derivative of function 2
    dataGraph = new QCPDataMap();
    for(double i = 0;i<MAXIMUM_RANGE;i+=PACE)
    {
        if(i != 1)
        {
            dataGraph->insert(i,QCPData(i,SecondDerivative(i,&Function2)));
        }
    }
    MGraph->addPlot(dataGraph,"f2''(x)");
}

/**
 * @brief CentralWidget::Function1
 * @param x
 * @return
 */
double WCentralWidget::Function1(double x)
{
    return pow(x,5) + pow(x,3) * 5 + 2 * x;
}

/**
 * @brief CentralWidget::Function2
 * @param x
 * @return
 */
double WCentralWidget::Function2(double x)
{
    return x / (1-pow(x,2));
}

/**
 * @brief CentralWidget::Derivative
 * @param x
 * @param f : the function to derivate
 * @return Derivated function f'(x)
 */
double WCentralWidget::Derivative(double x, double(*f)(double))
{
    return (8*(f(x+(H/2)) - f(x-(H/2))) - f(x+H) + f(x-H))/(6*H);
}

/**
 * @brief CentralWidget::SecondDerivative
 * @param f : the function to derivate
 * @return Derivated function f''(x)
 */
double WCentralWidget::SecondDerivative(double x, double (*f)(double))
{
    return (f(x+H) + f(x-H) -  2*f(x))/(H*H);
}
