#include "params.h"


namespace NMySpace::NPhan::NEoS {
   
    TDimlessParams TDimlessParamsFactory::Build(double P) const {
        return TDimlessParams(TParamsBase{
            .T = T,
            .A = P*A,
            .B = P*B,
        }, P);
    }
    
}
