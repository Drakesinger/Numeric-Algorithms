/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#ifndef RK_H
#define RK_H

#include "pendulum.h"

class RK : public TwoNodes
{
public:
    RK(const OneNode& upper, const OneNode& lower,
                      double dt=0.005, double g=9.81);

    const char *solverMethod();

    void solve(const double *yin, double *yout);
};

#endif // RK_H
