#ifndef RECTANGLERANDOMSTEPINTEGRALE_H
#define RECTANGLERANDOMSTEPINTEGRALE_H

#include "integrale.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */
class RectangleRandomStepIntegrale : public Integrale
{
public:
    RectangleRandomStepIntegrale(double begin, double end,  const Function &f);
    virtual ~RectangleRandomStepIntegrale();

protected:
    virtual double integrate();
};

#endif // RECTANGLERANDOMSTEPINTEGRALE_H
