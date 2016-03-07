#include "linearfunction.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

LinearFunction::LinearFunction()
{

}

LinearFunction::~LinearFunction()
{

}

double LinearFunction::f(double x) const
{
    return x;
}

Function *LinearFunction::clone() const
{
    return new LinearFunction(*this);
}

