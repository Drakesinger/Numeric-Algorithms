#include "../include/MultipleSolutions.h"
#include "../include/FixePointSolve.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const double MultipleSolutions::epsilon = 0.001;

MultipleSolutions::MultipleSolutions(double begin, double end, double step, Equation *e) :
    begin(begin), end(end), step(step), equation(e)
{

}

MultipleSolutions::~MultipleSolutions()
{
    //dtor
}

std::set<double> MultipleSolutions::solve() const
{
    std::set<double> result;

    double lastSolution = 0;
    for(double i = begin; i < end; i += step)
    {
        try
        {
            double solution = 0;
            FixePointSolve f(i, equation);
            solution = (f.getSolution());
            if(abs(solution - lastSolution) > epsilon)
            {
                result.insert(solution);
                lastSolution = solution;
            }
        }
        catch(int ex)
        {
            //Nothing to show, there is not a solution
        }
    }

    return result;
}
