/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#include "datawidget.h"
#include <QtWidgets>

WDataWidget::WDataWidget(QWidget *parent) :QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    MLabelBuy = new QLabel("Good dates to buy",this);
    MLabelSell = new QLabel("Good dates to sell",this);
    TextBuy = new QPlainTextEdit(this);
    TextSell = new QPlainTextEdit(this);
    TextSell->setReadOnly(true);
    TextBuy->setReadOnly(true);

    layout->addWidget(MLabelBuy);
    layout->addWidget(TextBuy);
    layout->addWidget(MLabelSell);
    layout->addWidget(TextSell);
}

void WDataWidget::SetBuyText(QString texte)
{
    TextBuy->appendPlainText(texte);
}

void WDataWidget::SetSellText(QString texte)
{
    TextSell->appendPlainText(texte);
}
