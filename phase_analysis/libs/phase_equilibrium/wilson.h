#pragma once

#include <phase_analysis/libs/properties/pure_substance.h>


namespace MySpace::PhAn {
    
    // Расчет давления насыщения по формулам Вильсона. 
    // Используется в том числе для начального приближения K-values.
    double computePsWilson(const PureSubstanceProps& props, double T);
    
} // namespace MySpace::PhAn;