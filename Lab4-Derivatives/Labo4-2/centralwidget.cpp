/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#include "centralwidget.h"
#include "datawidget.h"
#include "graph.h"
#include "qcustomplot.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QLayout>
#include <QtWidgets>
#include <QDebug>
#include <QTime>

#define H 0.00000001

WCentralWidget::WCentralWidget(QWidget *parent) : QWidget(parent)
{
    MGraph = new Graph(this);
    MDataWidget = new WDataWidget(this);

    QGridLayout* GridLayout = new QGridLayout(this);
    GridLayout->addWidget(MGraph,0,0,1,15);
    GridLayout->addWidget(MDataWidget,0,21,1,5);

    OpenCSV();
}

/**
 * @brief WCentralWidget::OpenCSV
 * Opens the CSV file that contains the info on the prices of rare soil.
 */
void WCentralWidget::OpenCSV()
{
    QCPDataMap* DataGraph = new QCPDataMap();
    QString FileName = ":/csv/csv/163490.csv";
    double Index = 0.0;
    QFile File(FileName);

    // Read the file.
    if(File.open(QIODevice::ReadOnly))
    {
        QString Data = File.readAll();
        Data.remove(QRegExp("\r"));
        QString Temp;
        QChar Character;
        QTextStream TextStream(&Data);
        QDateTime Time;

        while(!TextStream.atEnd())
        {
            TextStream >> Character;

            // Used for floats (values are comma separated and also comma-contained, Excel and French... go figure)
            if(Character==',')
            {
                Character='.';
            }

            // End of line or word
            if(Character == ';' || Character =='\n')
            {
                //On ne traite pas la colonne "CHF" du fichier
                if(Temp != "CHF")
                {
                    bool IsConversionSucessful = true;

                    // Convert to a DateTime value, if sucessful, it can be inserted as an index and used on the x-axis
                    Time = QDateTime::fromString(Temp,"yyyy-MM-dd");
                    if(Time.isValid())
                    {
                        Index = Time.toTime_t();
                    }

                    // Convert to a double, if sucessful, it's a price that goes in the y-coodrdinate field.
                    Temp.toDouble(&IsConversionSucessful);
                    if(IsConversionSucessful)
                    {
                        // Add the number to the DataGraph.
                        DataGraph->insert(Index,QCPData(Index,Temp.toDouble()));
                    }
                }
                Temp="";
            }
            else
            {
                Temp.append(Character);
            }
        }

        MGraph->AddPlot(DataGraph,"Rare Soil");
        File.close();

        // Get the usefull data only.
        double X[DataGraph->size()];
        double XDate[DataGraph->size()-1];
        double Y[DataGraph->size()];

        QCPDataMap::iterator iterateur;
        int i = 0;
        for(iterateur = DataGraph->begin();iterateur != DataGraph->end();iterateur++)
        {
            XDate[i] = iterateur->key;
            Y[i] = iterateur->value;
            i++;
        }

        double DerivativeValue[DataGraph->size()-1];

        for(int j = 0;j<DataGraph->size();j++)
        {
            if(j != 0)
            {
                double value = Derivative(Y[j-1],Y[j], XDate[j-1],XDate[j]);
                DerivativeValue[j-1] = value;
                X[j-1] = XDate[j-1];
            }
        }
        FillTextFields(DerivativeValue, X, DataGraph->size()-1);
    }
}

/**
 * @brief WCentralWidget::Derivative
 * @param y1
 * @param y2
 * @param x1
 * @param x2
 * @return
 */
double WCentralWidget::Derivative(double y1, double y2, double x1, double x2)
{
    return (y2-y1) / (x2-x1);
}

/**
 * @brief WCentralWidget::FillTextFields
 * Fills the text fiels in the DataWidget
 *
 * Algorithm:
 * Check the sign of the slope for each point.
 * If the sign changes, the function either increases or decreases.
 * Sign positive -> negative => prices go downn -> SELL
 * Sign negative -> positive = > proces go up -> BUY
 *
 * @param DerivateValues
 * @param X
 * @param Range
 */
void WCentralWidget::FillTextFields(double* DerivateValues ,double* X, int Range)
{
    QString TextBuy = "";
    QString TextSell = "";
    int Status = 1;

    for(int i = 1; i<Range;i++)
    {
        if(Status == 1)
        {
            if(DerivateValues[i] < 0)
            {
                TextSell += QDateTime::fromTime_t(X[i]).toString("yyyy-MM-dd") + "\n";
                Status = -1;
            }
        }
        else
        {
            if(DerivateValues[i] < 0)
            {
                TextBuy += QDateTime::fromTime_t(X[i]).toString("yyyy-MM-dd") + "\n";
                Status = 1;
            }
        }
    }

    MDataWidget->SetBuyText(TextBuy);
    MDataWidget->SetSellText(TextSell);
}
