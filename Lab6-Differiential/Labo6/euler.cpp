/**
 * Authors:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

#include "euler.h"

Euler::Euler(const OneNode& upper,
                                         const OneNode& lower,
                                         double dt, double g):
    TwoNodes(upper, lower, dt, g)
{
}

const char *Euler::solverMethod()
{
    return "Euler";
}

void Euler::solve(const double *yin, double *yout)
{
    double dydx[NUM_EQNS];

    // Calculate the derivatives of the equations at time + dt
    derivate(yin, dydx);

    // Update the values of theta and omega for the two nodes
    yout[THETA_1] = yin[THETA_1] + dydx[THETA_1] * m_dt;
    yout[OMEGA_1] = yin[OMEGA_1] + dydx[OMEGA_1] * m_dt;

    yout[THETA_2] = yin[THETA_2] + dydx[THETA_2] * m_dt;
    yout[OMEGA_2] = yin[OMEGA_2] + dydx[OMEGA_2] * m_dt;
}
