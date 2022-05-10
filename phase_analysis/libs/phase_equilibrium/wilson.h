#pragma once

#include <phase_analysis/libs/properties/pure_substance.h>


namespace NMySpace::NPhan::NPheq {
    
    // Расчет давления насыщения по формулам Вильсона. 
    // Используется в том числе для начального приближения K-values.
    double ComputePsWilson(const TPureSubstanceProps& props, double T);
    
}
