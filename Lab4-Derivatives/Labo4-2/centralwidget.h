/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#ifndef WIDGETCENTRAL_H
#define WIDGETCENTRAL_H

#include <QWidget>
#include "qcustomplot.h"

class Graph;
class WDataWidget;

class WCentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WCentralWidget(QWidget *parent = 0);

signals:

public slots:

private:
    Graph* MGraph;
    WDataWidget* MDataWidget;

    void OpenCSV();
    void ProcessData();
    double Derivative(double y1, double y2, double x1, double x2);
    void FillTextFields(double* DerivateValues, double* X, int Range);
};

#endif // WIDGETCENTRAL_H
