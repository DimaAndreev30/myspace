#include "wilson.h"

#include <cmath>


namespace MySpace::PhAn {
    
    double computePsWilson(const PureSubstanceProps& props, double T)
    {
        return props.Pc*std::exp(5.31*(1 + props.w)*(1 - props.Tc/T));
    }
    
} // namespace MySpace::PhAn;
