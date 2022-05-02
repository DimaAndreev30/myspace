#include "SRK.h"

#include "constants.h"

#include <cmath>


namespace NMySpace::NPhan::NEoS {
    
    TSRK::TSRK(): TCubicEoS(0, 1, OmegaA0_SRK, OmegaB0_SRK, "SRK") {}
    
    double TSRK::AlphaT(double Tr, double w) const {
        double temp = (1 + GetSRK_M(w)*(1 - std::sqrt(Tr)));
        return temp*temp;
    }
    
}
