#include "PR.h"

#include "constants.h"

#include <cmath>


namespace NMySpace::NPhan::NEoS {
    
    TPR::TPR()
        : TCubicEoS(1 + SQRT_TWO, 1 - SQRT_TWO, OmegaA0_PR, OmegaB0_PR, "PR")
    {
    }
    
    double TPR::alphaT(double Tr, double w) const {
        double temp = (1 + getPR_M(w)*(1 - std::sqrt(Tr)));
        return temp*temp;
    }
    
}
