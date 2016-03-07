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

#include "graph.h"
#include <cmath>
#include <vector>

/**
 * @brief Create a instance of Graph
 * @param parent of the graph
 */
Graph::Graph(QWidget *parent) : QCustomPlot(parent)
{
    //Enable the zoom and drag functionalities
    //Enable the possibilities to select a plot
    this->setInteraction(QCP::iRangeZoom);
    this->setInteraction(QCP::iRangeDrag);
    this->setInteraction(QCP::iSelectPlottables);

    this->mouseIsPressed = false;
    this->key0isPressed = false;
    this->isXAxisBlocked = false;
    this->haveAddedAGraph = false;


    //Define how react the drag
    this->axisRect(0)->setRangeDrag(Qt::Horizontal | Qt::Vertical);
     //Define on which axis the zoom is performed
    this->axisRect(0)->setRangeZoom(Qt::Horizontal | Qt::Vertical);
    this->axisRect(0)->setRangeZoomAxes(this->xAxis,this->yAxis);

    //Define the QRubberBand for the selection rectangle
    rubberBandSelection = new QRubberBand(QRubberBand::Rectangle, this);

    //Connect signals and slots
    connect(this,SIGNAL(keyPressed(QKeyEvent*)),this,SLOT(moveGraph(QKeyEvent*)));
    //Zoom
//    connect(this->xAxis,SIGNAL(rangeChanged(QCPRange,QCPRange)),this,SLOT(zoomGraphX(QCPRange,QCPRange)));
//    connect(this->yAxis,SIGNAL(rangeChanged(QCPRange)),this,SLOT(zoomGraphY(QCPRange)));
    connect(this, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    connect(this,SIGNAL(selectionChangedByUser()),this,SLOT(changeLegend()));

    //Tooltip configuration
    this->setToolTipDuration(0);

    this->legend->setVisible(true);

    //change the number of tick on the graph.
    this->axisRect()->setRangeZoomFactor(0.9,0.9);
}

/**
 * @brief add a plot to the graph by using the data contain in "data"
 * @param data containt the points of our plot
 */
void Graph::AddPlot(QCPDataMap *data, QString namePlot)
{
    QString COLOURS_PEN_DEFAULT[12] = {"blue","red","green","black","orange","purple","gray","yellow","cyan","magenta","darkgray","pink"};
    QCPGraph *plot = new QCPGraph(this->xAxis,this->yAxis);
    QPen *pen;
    if(this->plottableCount()<12)
    {
        pen = new QPen(QColor(COLOURS_PEN_DEFAULT[this->plottableCount()]));
    }
    else
    {
        pen = new QPen(QColor(getRandomNum(256),getRandomNum(256),getRandomNum(256)));
    }

    plot->setLineStyle(QCPGraph::lsLine);
    plot->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,2));
    plot->setPen(*pen);
    plot->addData(*data);

    //Add the plot to the graphic
    this->addPlottable(plot);

    //take the max values of each axis
        if(this->yUpper < this->getMaxValue(data) || this->plottableCount() == 0)
        {
            this->yUpper = this->getMaxValue(data);
        }

        //take the min values of each axis
        if(this->yLower > this->getMinValue(data) || this->plottableCount() == 0)
        {
            this->yLower = this->getMinValue(data);
        }
         plot->setName(namePlot);

         // configure bottom axis to show date and time instead of number:
         this->xAxis->setTickLabelType(QCPAxis::ltDateTime);
         this->xAxis->setDateTimeFormat("yyyy-MM-dd");
         // set a more compact font size for bottom and left axis tick labels:
         this->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
         this->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
         // set a fixed tick-step to one tick per month:
         this->xAxis->setAutoTickStep(false);
         this->xAxis->setTickStep(2628000*6); // one month in seconds
         //this->xAxis->setTickStep(86400);
         this->xAxis->setSubTickCount(3);

         //end xAxis Date

        //Add the plot to the graphic
        this->addPlottable(plot);

        //Adjust axis to the new plot
        this->yAxis->setRange(yLower,yUpper);
        this->xAxis->setRange(data->firstKey(),data->lastKey());
         //this->xAxis->setRange(now - (86400 * 2),now);


    plot->addToLegend();
    this->haveAddedAGraph = true;
    this->actualSelectedPlotIndex = -1;
    replot();
}

/**
 * @brief Remove all plots of the graph
 */
void Graph::removeAllPlots()
{
    while(this->plottableCount() > 0)
    {
        this->removePlottable(0);
    }
    this->replot();
}

/**
 * @brief Return the width of the graph widget in pixel unit
 * @return the number of pixels in a int
 */
int Graph::getXAxisPixelLength()
{
    double upper = this->xAxis->coordToPixel(this->xAxis->range().upper);
    double lower = this->xAxis->coordToPixel(this->xAxis->range().lower);
    double range = upper-lower;
    return (int)range;
}

/**
 * @brief Return the height of the graph widget in pixel unit
 * @return the number of pixels in a int
 */
int Graph::getYAxisPixelLength()
{
    double upper = this->yAxis->coordToPixel(this->yAxis->range().upper);
    double lower = this->yAxis->coordToPixel(this->yAxis->range().lower);
    double range = upper-lower;
    return (int)range;
}


/**
 * @brief Move the graph on the x axis using the step given in parameter
 * @param step define the jump our graph do
 */
void Graph::moveGraphXAxis(float step)
{
    this->xAxis->setRangeLower(this->xAxis->range().lower +step);
    this->xAxis->setRangeUpper(this->xAxis->range().upper +step);
    this->replot();
}

/**
 * @brief Move the graph on the y axis using the step given in parameter
 * @param step define the jump our graph do
 */
void Graph::moveGraphYAxis(float step)
{
    this->yAxis->setRangeLower(this->yAxis->range().lower +step);
    this->yAxis->setRangeUpper(this->yAxis->range().upper +step);
    this->replot();
}

/**
 * @brief Detect when the mouse button is pressed and start the selection rectangle (if the right button is pressed)
 * @param event is handled by Qt
 */
void Graph::mousePressEvent(QMouseEvent *event)
{
    //We place our Rubberband and show it
    if(event->button() == Qt::RightButton)
        {
        rubberBandOrigin = event->pos();
        rubberBandSelection->setGeometry(QRect(rubberBandOrigin, QSize()));
        rubberBandSelection->show();
    }
    else if(event->button() == Qt::LeftButton)
    {
        mouseIsPressed = true;
    }
    QCustomPlot::mousePressEvent(event);
}

/**
 * @brief Detect when the mouse is moving and change the selection rectancle if it's visible.
 * @param event is handled by Qt
 */
void Graph::mouseMoveEvent(QMouseEvent *event)
{
    //It just adapt the selection rectangle to the mouse's move
    if(rubberBandSelection->isVisible())
    {
        rubberBandSelection->setGeometry(QRect(rubberBandOrigin, event->pos()).normalized());
    }
     QCustomPlot::mouseMoveEvent(event);
}

/**
 * @brief zoom (or unzoom) by using the coordinates givent in parameters
 * @param xp1
 * @param xp2
 * @param yp1
 * @param yp2
 */
void Graph::zoom(int xp1, int xp2, int yp1,int yp2)
{
   //r = (((hSel*WGraphe)/HGraphe)-wSel)/2;
   int r = (((abs(yp2-yp1)*this->width())/this->height())-abs(xp2-xp1))/2;


   double x1 = xAxis->pixelToCoord(xp1-r);
   double x2 = xAxis->pixelToCoord(xp2+r);
   double y1 = yAxis->pixelToCoord(yp1);
   double y2 = yAxis->pixelToCoord(yp2);

   this->xAxis->setRange(x1,x2);
   this->yAxis->setRange(y1,y2);
}

/**
 * @brief Detect if the mouse button is released and zoom on the graph in the area selected by the user
 * @param event is handled by Qt
 */
void Graph::mouseReleaseEvent(QMouseEvent *event)
{
    if (rubberBandSelection->isVisible())
        {
            //We take the geometry of our rubberband (who is our selection rectangle)
            //And we put it in QCustomGraph coordinate and change the range of the graph
            //Then we hide the Rubberband and replot our graph
            const QRect & zoomRect = rubberBandSelection->geometry();
            int xp1, yp1, xp2, yp2;
            zoomRect.getCoords(&xp1, &yp1, &xp2, &yp2);
            //We just check if the area of the rubberband isn't too small (to avoid user to juste right click and zoom)
            if(abs(xp2-xp1) > 10 || abs(yp2-yp1)>10)
            {
                zoom(xp1, xp2, yp1,yp2);
            }

            rubberBandSelection->hide();
            replot();
        }

    if(event->button() == Qt::LeftButton)
    {
        mouseIsPressed = false;
    }
    QCustomPlot::mouseReleaseEvent(event);
}

/**
 * @brief Let the user move the graph with the arrow keys of the keaboard
 * @param event is handled by Qt
 */
void Graph::moveGraph(QKeyEvent *event)
{
    const float step = 0.1;
    if(event->key() == Qt::Key_Up)
    {
        this->moveGraphYAxis(step);
    }
    else if(event->key() == Qt::Key_Down)
    {
        this->moveGraphYAxis(-step);
    }
    else if(event->key() == Qt::Key_Left)
    {
        this->moveGraphXAxis(-step);
    }
    else if(event->key() == Qt::Key_Right)
    {
        this->moveGraphXAxis(step);
    }
    else if(event->key() == Qt::Key_0)
    {
        this->key0isPressed = true;
        this->xAxis->setRange(xLower, xUpper);
        this->yAxis->setRange(yLower,yUpper);
        this->key0isPressed = false;

        replot();
    }
}

/**
 * @brief Graph::getRandomNum return a random number between 0 and max-1.
 * @param max is a int and will not be included in the interval
 * @return a random int between 0 and max-1
 */
int Graph::getRandomNum(int max)
{
    return rand() % max;
}

/**
 * @brief Graph::getMaxValue Give the maximum values in a QCPDatamap
 * @param data is a QCPDatamap who contains the plot's data
 * @return the maximum value in the QCPDatamap as double
 */
double Graph::getMaxValue(QCPDataMap *data)
{
    double max = 0;
    typedef QMap<double,QCPData>::iterator it_type;
    for(it_type iterator = data->begin();iterator != data->end();iterator++)
    {
        iterator.value();
        if(iterator.value().value > max)
        {
            max = iterator.value().value;
        }
    }
    return max;
}
/**
 * @brief Graph::getMinValue Give the minimum values in a QCPDatamap
 * @param data is a QCPDatamap who contains the plot's data
 * @return the minimum value in the QCPDatamap as double
 */
double Graph::getMinValue(QCPDataMap *data)
{
    double min = 0;
    typedef QMap<double,QCPData>::iterator it_type;
    for(it_type iterator = data->begin();iterator != data->end();iterator++)
    {
        iterator.value();
        if(iterator.value().value < min)
        {
            min = iterator.value().value;
        }
    }
    return min;
}

/**
 * @brief Graph::zoomGraphX limit the zoom capacity at a fixed number
 * @param newRange
 * @param oldRange
 */
void Graph::zoomGraphX(QCPRange newRange, QCPRange oldRange)
{
    if(newRange == oldRange)
    {
        this->isXAxisBlocked = true;
    }
    else
    {
        this->isXAxisBlocked = false;
    }
}

/**
 * @brief Graph::zoomGraphY limit the zoom capacity at a fixed number
 * @param newRange
 * @param oldRange
 */
void Graph::zoomGraphY(QCPRange newRange)
{
    if(!isXAxisBlocked || haveAddedAGraph)
    {
        oldRangeY = newRange;
        this->haveAddedAGraph=false;
    }
    else
    {
        this->yAxis->setRange(oldRangeY);
    }
}

/**
 * @brief Graph::renameAxis let the user change the axis labels
 * @param xAxisLabel is the new text for the xAxis Label
 * @param yAxisLabel is the new text for the yAxis Label
 */
void Graph::renameAxis(QString xAxisLabel, QString yAxisLabel)
{
    this->xAxis->setLabel(xAxisLabel);
    this->yAxis->setLabel(yAxisLabel);
}

/**
 * @brief Graph::showPointToolTip shows the coordinates (in graphic coordinate) in a tooltip when the mouse is on the graphic Widget
 * @param event is handled by Qt
 */
void Graph::showPointToolTip(QMouseEvent *event)
{
    double x = this->xAxis->pixelToCoord(event->pos().x());
    double y = this->yAxis->pixelToCoord(event->pos().y());
    this->setToolTip(QString(QDateTime::fromTime_t(x).toString("yyyy-MM-dd") + " , %1").arg(y));
}

/**
 * @brief Graph::changeLegend show the legend of a plot which is selected
 */
void Graph::changeLegend()
{
    foreach (QCPAbstractPlottable *plot, this->selectedPlottables()) {
        int indexPlot = getIndexPlottable(plot);
        if(indexPlot != -1)
        {
            //plot->setName("Courbe " + QString::number((indexPlot+1)));
            plot->setSelected(true);
            //Change the pen of the plot
            QPen *penSelection = new QPen(plot->pen());
            penSelection->setWidthF(3.0);
            plot->setPen(*penSelection);

            //restaure a normal pen to the last selected plot (before the new one)
            if(actualSelectedPlotIndex != -1)
            {
                QPen *penNormal = new QPen(this->plottable(actualSelectedPlotIndex)->pen());
                penNormal->setWidthF(1.0);
                this->plottable(actualSelectedPlotIndex)->setPen(*penNormal);
            }
            actualSelectedPlotIndex = indexPlot;
        }
        this->legend->clearItems();
        plot->addToLegend();
        this->legend->setVisible(true);
    }
    this->replot();
}

/**
 * @brief Graph::getIndexPlottable search and return the index of a plottable
 * @param plot is a AbstractPlottable
 * @return the index of the plot or -1 if the plot isn't in the list
 */
int Graph::getIndexPlottable(QCPAbstractPlottable *plot)
{
    for(int i = 0; i<this->plottableCount();i++)
    {
        if(this->plottable(i)== plot)
        {
            return i;
        }
    }
    return -1;
}
