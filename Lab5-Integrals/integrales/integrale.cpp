#include "integrale.h"
#include "functions/function.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

Integrale::Integrale(double begin, double end, const Function &f)
{
    this->begin = begin;
    this->end = end;
    this->f = f.clone();
}

Integrale::~Integrale()
{
    delete f;
}

double Integrale::getResult()
{
    if(!done)
    {
        result = integrate();
    }
    return result;
}

double Integrale::getBegin() const
{
    return begin;
}

double Integrale::getEnd() const
{
    return end;
}

const Function &Integrale::getFunction() const
{
    return *f;
}
