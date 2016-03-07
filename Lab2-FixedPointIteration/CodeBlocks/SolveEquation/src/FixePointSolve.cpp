/**
	Haute Ecole Arc
	Cours d'Algorithme Numerique
	Labo 2

	@author Equipe 5 (Mut Horia, Ryter Nils, Yakovenko Roman)
	@date 2015-04-30
 */

#include "../include/FixePointSolve.h"
#include "../equations/Equation.h"
#include <math.h>

const double FixePointSolve::valMax = 1E+200;
const double FixePointSolve::epsilon = 0.00001;
const double FixePointSolve::maxIteration = 1000;
const double FixePointSolve::lambda = 1;

FixePointSolve::FixePointSolve(double start,  Equation *e)
{
    this->start = start;
    this->solution = 0;
    this->equation = e;
}

FixePointSolve::~FixePointSolve()
{
    //dtor
}

double FixePointSolve::getSolution()
{
    solve();
    return solution;
}

void FixePointSolve::solve()
{
    double delta = epsilon+1;
    double x = start;
    int cptLoop = 0;

    while (delta > epsilon && cptLoop < maxIteration)
    {
	    double _yx = yx(x);
	    double _gx = gx(x);

	    x = _gx;

	    if(x > valMax) break;
	    delta = fabs( _gx - _yx);

        ++cptLoop;
    }

    if(x > valMax)
    {
        //WARNING : x out of range
        throw -1;
    }

    if(cptLoop >= maxIteration)
    {
        //WARNING : maximum iteration reached
        throw -2;
    }

    solution = x;
}

double FixePointSolve::gx(double x)
{
    return x + lambda* (equation->fx(x));
}

double FixePointSolve::yx(double x)
{
    return x;
}
