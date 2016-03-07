#ifndef EQUATION_H
#define EQUATION_H


class Equation
{
    public:
        Equation();
        virtual ~Equation();

        virtual double fx(double x) const = 0;
    protected:
    private:
};

#endif // EQUATION_H
