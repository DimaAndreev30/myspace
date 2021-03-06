#include "RK.h"

#include "constants.h"

#include <cmath>


namespace NMySpace::NPhan::NCubicEoS {
    
    TRK::TRK(): TCubicEoS(0, 1, OmegaA0_RK, OmegaB0_RK, "RK") {}
    
    double TRK::AlphaT(double Tr, double w) const {
        return 1/std::sqrt(Tr);
    }
    
}
