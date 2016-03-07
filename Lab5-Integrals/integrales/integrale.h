#ifndef INTEGRALE_H
#define INTEGRALE_H

class Function;

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */
class Integrale
{
public:
    Integrale(double begin, double end, const Function &f);
    virtual ~Integrale();

    double getResult();
    double getBegin() const;
    double getEnd() const;
    const Function &getFunction() const;

protected:
    virtual double integrate() = 0;

private:
    bool done;
    double result;
    double begin;
    double end;
    const Function *f;
};

#endif // INTEGRALE_H
