#ifndef FUNCTION_H
#define FUNCTION_H

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */
class Function
{
public:
    Function();
    virtual ~Function();

    virtual double f(double x) const = 0;
    virtual Function *clone() const = 0;
};

#endif // FUNCTION_H
