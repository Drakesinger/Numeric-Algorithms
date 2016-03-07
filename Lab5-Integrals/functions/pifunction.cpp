#include "pifunction.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

PiFunction::PiFunction()
{

}

PiFunction::~PiFunction()
{

}

double PiFunction::f(double x) const
{
    return 1 / (1 + (x*x));
}

Function *PiFunction::clone() const
{
    return new PiFunction(*this);
}

