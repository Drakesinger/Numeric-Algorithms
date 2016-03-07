#include "rectanglefixstepintegrale.h"
#include "functions/function.h"
#include "functions/pifunction.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

RectangleFixStepIntegrale::RectangleFixStepIntegrale(double begin, double end, const Function &f, double step) : Integrale(begin, end, f)
{
    this->step = step;
}

RectangleFixStepIntegrale::~RectangleFixStepIntegrale()
{

}

double RectangleFixStepIntegrale::integrate()
{
    const Function &function = getFunction();
    double totalArea = 0;

    for(double x = getBegin(); x < getEnd(); x += step)
    {
        double h = function.f(x);
        double w = step;

        double area = h*w;
        totalArea += area;
    }
    return totalArea;
}

