/**
  * Original Authors:
  * Lucas Beltrame Nicolas Gonin Alexandre Straubhaar
  *
  * Created during the Qt P2.
  *
  * Dependency: QCustomPlot
  * http://qcustomplot.com/
  *
  * HAS NOT BEEN CHANGED
  */

#pragma once

#include "qcustomplot.h"

class Graph : public QCustomPlot
{
    Q_OBJECT

public:
    Graph(QWidget *parent);
    void addPlot(QCPDataMap *data, QString namePlot);
    void removeAllPlots();
    int getXAxisPixelLength();
    int getYAxisPixelLength();
    void moveGraphXAxis(float step);
    void moveGraphYAxis(float step);
    void zoom(int xp1, int xp2, int yp1,int yp2);
    void renameAxis(QString xAxisLabel = "X", QString yAxisLabel = "Population [%]");

private:
    int getRandomNum(int max);
    double getMaxValue(QCPDataMap *data);
    double getMinValue(QCPDataMap *data);
    int getIndexPlottable(QCPAbstractPlottable *plot);

    int actualSelectedPlotIndex;
    QRubberBand *rubberBandSelection;
    QPoint rubberBandOrigin;
    float xLower;
    float xUpper;
    float yLower;
    float yUpper;
    QCPRange oldRangeY;
    bool mouseIsPressed;
    bool key0isPressed;
    bool isXAxisBlocked;
    bool haveAddedAGraph;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void keyPressed(QKeyEvent *);

public slots:
    void moveGraph(QKeyEvent *event);
    void zoomGraphX(QCPRange newRange,QCPRange oldRange);
    void zoomGraphY(QCPRange newRange);
    void showPointToolTip(QMouseEvent *event);
    void changeLegend();
};
