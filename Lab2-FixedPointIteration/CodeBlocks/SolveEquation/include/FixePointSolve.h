/**
	Haute Ecole Arc
	Cours d'Algorithme Numerique
	Labo 2

	@author Equipe 5 (Mut Horia, Ryter Nils, Yakovenko Roman)
	@date 2015-04-30
 */

#ifndef FIXEPOINTSOLVE_H
#define FIXEPOINTSOLVE_H

class Equation;

class FixePointSolve
{
    public:
        FixePointSolve(double start, Equation *e);
        virtual ~FixePointSolve();
        double getSolution();
    protected:
    private:
        double start;
        double solution;
        Equation *equation;
        void solve();

        double fx(double x);
        double gx(double x);
        double yx(double x);

        static const double valMax;
        static const double epsilon ;
        static const double maxIteration;
        static const double lambda;
};

#endif // FIXEPOINTSOLVE_H
