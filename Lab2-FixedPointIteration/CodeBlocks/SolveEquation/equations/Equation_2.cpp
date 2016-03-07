#include "Equation_2.h"
#include <math.h>

Equation_2::Equation_2()
{
    //ctor
}

Equation_2::~Equation_2()
{
    //dtor
}

double Equation_2::fx(double x) const
{
    return sin(x) + x / 13;
}
