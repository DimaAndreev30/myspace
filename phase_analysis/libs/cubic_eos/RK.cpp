#include "RK.h"

#include "constants.h"

#include <cmath>


namespace MySpace::PhAn::EoS {
    
    RKInterface::RKInterface()
        : Interface(0, 1, OmegaA0_RK, OmegaB0_RK, "RK")
    {
    }
    
    double RKInterface::alphaT(double Tr, double w) const {
        return 1/std::sqrt(Tr);
    }
    
} // namespace MySpace::PhAn::EoS;