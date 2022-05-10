#include "params.h"


namespace NMySpace::NPhan::NCubicEoS {
   
    TDimlessParams TDimlessParamsWOPressure::With(double P) const {
        return TParamsBase{
            .A = P*A,
            .B = P*B,
        };
    }
    
}
