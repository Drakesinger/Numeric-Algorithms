/**
  * Authors:
  * Horia Mut, Nils Ryter, Romain Yakovenko
  */

#include "rightmenu.h"
#include <QtWidgets>

WRightMenu::WRightMenu(QWidget *parent) : QWidget(parent)
{
    // Set the size so that the layout doesn't stretch it.
    this->setMaximumWidth(125);

    // Initialize the radio buttons.
    MRadioButtonFunction1 = new QRadioButton("Function 1");
    MRadioButtonFunction2 = new QRadioButton("Function 2");
    MRadioButtonFunction1->setChecked(true);

    // Create a group for the radio buttons.
    MGroupBoxFunctionChoice = new QGroupBox("Function plot choice:",this);

    // Create a layout that will contain the radio buttons.
    QVBoxLayout* VBoxLayoutGroupBox = new QVBoxLayout();
    VBoxLayoutGroupBox->addWidget(MRadioButtonFunction1);
    VBoxLayoutGroupBox->addWidget(MRadioButtonFunction2);
    VBoxLayoutGroupBox->addStretch(1);
    MGroupBoxFunctionChoice->setLayout(VBoxLayoutGroupBox);

    // Create a layout for the right menu and add the group box to it.
    QVBoxLayout* VBoxLayoutRightMenu = new QVBoxLayout(this);
    VBoxLayoutRightMenu->addWidget(MGroupBoxFunctionChoice);

    // Connect the signals to plot the correct functions.
    connect(MRadioButtonFunction1,SIGNAL(toggled(bool)),this,SLOT(On_Toggle_RadioButtonFunction1(bool)));
    connect(MRadioButtonFunction2,SIGNAL(toggled(bool)),this,SLOT(On_Toggle_RadioButtonFunction2(bool)));

    connect(this,SIGNAL(DrawFunction1()),this->parent(),SLOT(DrawFunction1()));
    connect(this,SIGNAL(DrawFunction2()),this->parent(),SLOT(DrawFunction2()));

}

void WRightMenu::On_Toggle_RadioButtonFunction1(bool state)
{
    if(state)
    {
        emit(DrawFunction1());
    }
}

void WRightMenu::On_Toggle_RadioButtonFunction2(bool state)
{
    if(state)
    {
        emit(DrawFunction2());
    }
}
