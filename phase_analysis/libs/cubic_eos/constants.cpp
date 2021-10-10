#include "constants.h"


namespace MySpace::PhAn::EoS {
    
    const double R_CONST = 0.083144598484848;

    const double T_ZERO = 273.15;
    
    const double OmegaA0_RK  = 0.4274802,   OmegaB0_RK  = 0.08664035;
    const double OmegaA0_SRK = OmegaA0_RK,  OmegaB0_SRK = OmegaB0_RK;
    const double OmegaA0_PR  = 0.457235529, OmegaB0_PR  = 0.07796074;

    const double SQRT_TWO = 1.414213562373095;

    double getSRK_M (double w) {
        return 0.48 + w*(1.574 - w*0.176);
    }

    double getPR_M  (double w) {
        if (w < 0.49) return 0.37464 + w*(1.54226 - w*0.26992);
        else return 0.379642 + w*(1.48503 + w*(w*0.016666 - 0.164423));
    }
    
} // namespace MySpace::PhAn::EoS;
