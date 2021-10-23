#include "SRK.h"

#include "constants.h"

#include <cmath>


namespace MySpace::PhAn::EoS {
    
    SRKInterface::SRKInterface()
        : Interface(0, 1, OmegaA0_SRK, OmegaB0_SRK, "SRK")
    {
    }
    
    double SRKInterface::alphaT(double Tr, double w) const {
        double temp = (1 + getSRK_M(w)*(1 - std::sqrt(Tr)));
        return temp*temp;
    }
    
} // namespace MySpace::PhAn::EoS;
