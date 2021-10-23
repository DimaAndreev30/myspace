#include "PR.h"

#include "constants.h"

#include <cmath>


namespace MySpace::PhAn::EoS {
    
    PRInterface::PRInterface()
        : Interface(1 + SQRT_TWO, 1 - SQRT_TWO, OmegaA0_PR, OmegaB0_PR, "PR")
    {
    }
    
    double PRInterface::alphaT(double Tr, double w) const {
        double temp = (1 + getPR_M(w)*(1 - std::sqrt(Tr)));
        return temp*temp;
    }
    
} // namespace MySpace::PhAn::EoS;
