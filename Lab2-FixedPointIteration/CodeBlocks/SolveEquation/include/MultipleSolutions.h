#ifndef MULTIPLESOLUTIONS_H
#define MULTIPLESOLUTIONS_H

#include <iostream>
#include <set>

class Equation;

class MultipleSolutions
{
    public:
        MultipleSolutions(double begin, double end, double step, Equation *e);
        virtual ~MultipleSolutions();

        std::set<double> solve() const;

        const static double epsilon;
    protected:
    private:
        double begin;
        double end;
        double step;

        Equation *equation;
};

#endif // MULTIPLESOLUTIONS_H
