#include "wilson.h"

#include <cmath>


namespace NMySpace::NPhan::NPheq {
    
    double ComputePsWilson(const TPureSubstanceProps& props, double T) {
        return props.Pc*std::exp(5.31*(1 + props.w)*(1 - props.Tc/T));
    }
    
}
