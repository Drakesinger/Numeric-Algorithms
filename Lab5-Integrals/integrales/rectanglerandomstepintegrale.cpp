#include "rectanglerandomstepintegrale.h"

/*
 * Auteurs:
 * Horia Mut, Nils Ryter, Romain Yakovenko
 */

RectangleRandomStepIntegrale::RectangleRandomStepIntegrale(double begin, double end, const Function &f) :
    Integrale(begin, end, f)
{

}

RectangleRandomStepIntegrale::~RectangleRandomStepIntegrale()
{

}

double RectangleRandomStepIntegrale::integrate()
{
    /*TODO
     * pas le temps désolé. Mais comme vous
     * pouvez le constatez, la structure est
     * flexible et extensible, tant au niveau
     * des méthode d'intégration que des fonctions
     */
}

