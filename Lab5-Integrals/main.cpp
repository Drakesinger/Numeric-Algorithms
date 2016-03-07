#include <iostream>
#include <limits>
#include <cmath>
#include <stdlib.h>

#include "integrales/rectanglefixstepintegrale.h"
#include "integrales/rectanglerandomstepintegrale.h"
#include "functions/pifunction.h"
#include "functions/linearfunction.h"
#include "functions/sinfunction.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 *
 * Code réalisé sur Qt creator, mais normalement
 * compatible et compilable sur code blocs
 */

using namespace std;

//=============================================
//  DISPLAY
//=============================================

void showTitle(const string &s){
    cout<<""<<endl;
    cout<<""<<endl;
    cout<<"==================================="<<endl;
    cout<<s<<endl;
    cout<<"==================================="<<endl;
}

void showSubTitle(const string &s){
    cout<<""<<endl;
    cout<<s<<endl;
    cout<<"-----------------------------------"<<endl;
    cout<<""<<endl;
}

void clearScreen()
{
    for(int i = 0; i < 50; ++i)
    {
        cout<<endl;
    }
}

void showResult(double result)
{
    showSubTitle("Resultat de l'intégration");
    cout<<result<<endl;
    cout<<endl<<"Pressez une touche pour continuer"<<endl;
    cin.get();
    cin.ignore();
}

//=============================================
//  NAVIGATION
//=============================================

bool menuParameter(double *reslut, double *begin, double *end)
{
    double epsilon = std::numeric_limits<double>::epsilon();
    double min = std::numeric_limits<double>::min();
    double max= std::numeric_limits<double>::max();

    showSubTitle("Choix de l'epsilon");

    cout<<"L'espilon machine est de : "<<epsilon<<endl;
    cout<<endl<<"Entrez l'epsilon (ou entrez un nombre negatif pour utiliser l'espilon machine): ";

    double value = 0;
    cin>>value;
    cout<<endl;

    if(value < 0)
    {
        *reslut = epsilon;
    }
    else
    {
        *reslut = value;
    }

    showSubTitle("Choix des bornes de debut et de fin");
    cout<<"Entrez min ou max afin d'avoir la valeur min ou max d'un double : "<<endl;

    cout<<"Debut : ";
    string stringBegin;
    cin>>stringBegin;

    if(stringBegin == "min")
    {
        *begin = min;
    }
    else if(stringBegin == "max")
    {
        *begin = max;
    }
    else
    {
        *begin = atof(stringBegin.c_str());
    }

    cout<<"Fin : ";

    string stringEnd;
    cin>>stringEnd;
    cout<<endl;

    if(stringEnd == "min")
    {
        *end = min;
    }
    else if(stringEnd == "max")
    {
        *end = max;
    }
    else
    {
        *end = atof(stringEnd.c_str());
    }
}

bool menuMethod(Function &f, double *reslut)
{

    showSubTitle("Choix de la méthode d'integration");

    cout<<"1) rectangle fixe"<<endl;
    cout<<"2) rectange aléatoire (non fonctionnelle)"<<endl;
    cout<<"0) Quiter"<<endl;

    cout<<endl<<"Option choisie : ";

    int option = 0;
    cin>>option;
    cout<<endl;

    Integrale *integrale = 0;

    switch(option)
    {
    case 1:
    {
        double eps = 0;
        double begin = 0;
        double end = 0;
        menuParameter(&eps, &begin, &end);
        integrale = new RectangleFixStepIntegrale(begin, end, f, 2*eps);
        break;
    }
    case 2:
    {
        integrale = new RectangleRandomStepIntegrale(0, 1, f);
        break;
    }
    case 0:
        return false;
    default:
        return false;
    }

    if(integrale != 0)
    {
        *reslut = integrale->getResult();
        delete integrale;
    }

    return true;
}

bool mainMenu()
{
    clearScreen();
    showTitle("Menu principal");

    showSubTitle("Choix de la fonction à intégrer");

    cout<<"1) f(x) = x"<<endl;
    cout<<"2) f(x) = 1 / (1 + pow(x, 2))"<<endl;
    cout<<"3) f(x) = sin(x)"<<endl;
    cout<<"0) Retour"<<endl;

    cout<<endl<<"Option choisie : ";

    int optionMethode = 0;
    cin>>optionMethode;
    cout<<endl;

    Function *function = 0;
    double result = 0;

    switch(optionMethode)
    {
    case 1:
        function = new LinearFunction();
        break;
    case 2:
        function = new PiFunction();
        break;
    case 3:
        function = new SinFunction();
        break;
    case 0:
        return false;
    default:
        return false;
    }

    if(function != 0)
    {
        bool quit = menuMethod(*function, &result);
        delete function;
        showResult(result);
        return quit;
    }

    return true;
}

//=============================================
//  ENTRY POINT
//=============================================

int main()
{
    while(mainMenu());

    return 0;
}

