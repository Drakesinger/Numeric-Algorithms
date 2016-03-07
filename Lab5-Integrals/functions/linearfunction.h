#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H

#include "function.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */
class LinearFunction : public Function
{
public:
    LinearFunction();
    virtual ~LinearFunction();

    virtual double f(double x) const;
    virtual Function *clone() const;
};

#endif // LINEARFUNCTION_H
