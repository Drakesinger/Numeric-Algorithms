/**
	Haute Ecole Arc
	Cours d'Algorithme Numerique
	Labo 2

	@author Equipe 5 (Mut Horia, Ryter Nils, Yakovenko Roman)
	@date 2015-04-30
 */

#include <iostream>
#include <set>
#include <stdio.h>
#include "include/MultipleSolutions.h"
#include "equations/Equation_1.h"
#include "equations/Equation_2.h"
#include <assert.h>

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

//=============================================
//  NAVIGATION
//=============================================

void askRange(double &begin, double &end, double &step)
{
    cout<<"Entrez la valeur de DEBUT d'iteration :"<<endl;
	cin>>begin;

	cout<<"Entrez la valeur de FIN d'iteration :"<<endl;
	cin>>end;

	cout<<"Entrez la valeur de PAS d'iteration :"<<endl;
	cin>>step;

    assert(begin <= end);

	cout<<"Resume des valeurs choisies :"<<endl;
	cout<<"   DEBUT = "<<begin<<endl;
	cout<<"   FIN = "<<end<<endl;
	cout<<"   PAS = "<<step<<endl;
}

void showSolutions(set<double> result)
{
    cout<<endl<<"Hey ! Voici les solutions :"<<endl;

    while (!result.empty()) {
        cout << ' ' << *result.begin();
        result.erase(result.begin());
    }
    cout<<endl<<endl<<"pressez 'q' puis enter pour revenir au menu principal"<<endl;

    string pause;
    cin>>pause;
}

bool mainMenu()
{
    clearScreen();
    showTitle("Menu principal");
    showSubTitle("Choix de l'equation");

    cout<<"1) x/(1 - x*x)"<<endl;
    cout<<"2) sin(x) + x / 13;"<<endl;
    cout<<"0) Quiter"<<endl;

    cout<<endl<<"Option choisie : ";

    int option = 0;
    cin>>option;
    cout<<endl;

    Equation *e = 0;
    MultipleSolutions * m = 0;
    double begin = 0;
    double end = 10;
    double step = 0.01;

    switch(option)
    {
        case 1:
            askRange(begin, end, step);
            e = new Equation_1();
            m = new MultipleSolutions (begin, end, step, e);
            showSolutions(m->solve());
            delete m;
            delete e;
            break;
        case 2:
            askRange(begin, end, step);
            e = new Equation_2();
            m = new MultipleSolutions (begin, end, step, e);
            showSolutions(m->solve());
            delete m;
            delete e;
            break;
        case 3:
            break;
        case 0:
            return false;
        default:
            return false;

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
