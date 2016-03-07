#ifndef EQUATION_2_H
#define EQUATION_2_H

#include "Equation.h"

class Equation_2 : public Equation
{
    public:
        Equation_2();
        virtual ~Equation_2();

        virtual double fx(double x) const;
    protected:
    private:
};

#endif // EQUATION_2_H
