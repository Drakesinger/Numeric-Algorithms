#include "Equation_1.h"

Equation_1::Equation_1()
{
    //ctor
}

Equation_1::~Equation_1()
{
    //dtor
}

double Equation_1::fx(double x) const
{
    return x/(1 - x*x);
}
