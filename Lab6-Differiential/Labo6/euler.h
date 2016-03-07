/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#ifndef EULER_H
#define EULER_H

#include "pendulum.h"

class Euler : public TwoNodes
{
public:
    Euler(const OneNode& upper, const OneNode& lower,
                        double dt=0.05, double g=9.81);

    const char *solverMethod();

    void solve(const double *yin, double *yout);
};

#endif // EULER_H
