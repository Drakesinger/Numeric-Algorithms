#ifndef RECTANGLEINTEGRALE_H
#define RECTANGLEINTEGRALE_H

#include "integrale.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */
class RectangleFixStepIntegrale : public Integrale
{
public:
    RectangleFixStepIntegrale(double begin, double end,  const Function &f, double step);
    virtual ~RectangleFixStepIntegrale();

protected:
    double step;

    virtual double integrate();
};

#endif // RECTANGLEINTEGRALE_H
