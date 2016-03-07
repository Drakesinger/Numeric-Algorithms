#ifndef SINFUNCTION_H
#define SINFUNCTION_H

#include "function.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */
class SinFunction : public Function
{
public:
    SinFunction();
    ~SinFunction();

    virtual double f(double x) const;
    virtual Function *clone() const;
};

#endif // SINFUNCTION_H
