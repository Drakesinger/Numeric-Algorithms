/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#ifndef WIDGETINFORMATION_H
#define WIDGETINFORMATION_H

#include <QWidget>
class QPlainTextEdit ;
class QLabel;

class WDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WDataWidget(QWidget *parent = 0);
    void SetBuyText(QString texte);
    void SetSellText(QString texte);

signals:

public slots:

private:
    QLabel* MLabelBuy;
    QLabel* MLabelSell;
    QPlainTextEdit* TextBuy;
    QPlainTextEdit* TextSell;

};

#endif // WIDGETINFORMATION_H
