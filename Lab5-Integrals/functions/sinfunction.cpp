#include "sinfunction.h"
#include "math.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

SinFunction::SinFunction()
{

}

SinFunction::~SinFunction()
{

}

double SinFunction::f(double x) const
{
    return sin(x);
}

Function *SinFunction::clone() const
{
    return new SinFunction(*this);
}

