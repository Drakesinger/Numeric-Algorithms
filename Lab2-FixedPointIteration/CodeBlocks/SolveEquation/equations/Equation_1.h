#ifndef EQUATION_1_H
#define EQUATION_1_H

#include "Equation.h"

class Equation_1 : public Equation
{
    public:
        Equation_1();
        virtual ~Equation_1();

        virtual double fx(double x) const;
    protected:
    private:
};

#endif // EQUATION_1_H
