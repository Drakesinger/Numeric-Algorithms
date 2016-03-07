#ifndef PIFUNCTION_H
#define PIFUNCTION_H

#include "function.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */
class PiFunction : public Function
{
public:
    PiFunction();
    virtual ~PiFunction();

    virtual double f(double x) const;
    virtual Function *clone() const;
};

#endif // PIFUNCTION_H
