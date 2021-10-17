#include "two_phase_compos.h"


namespace MySpace::PhAn {
    
    TwoPhaseCompos::TwoPhaseCompos(size_t N)
    {
        x.reserve(N);
        y.reserve(N);
    }
    
    bool TwoPhaseCompos::setFromKValues(const std::vector<double>& kValues, 
                                        const std::vector<double>& z) {
        x.resize(z.size());
        y.resize(z.size());
        
        x[0] = (kValues[1] - 1)/(kValues[1] - kValues[0]);
        y[0] = kValues[0]*x[0];
        
        x[1] = 1 - x[0];
        y[1] = 1 - y[0];
        
        V = (z[0] - x[0])/(y[0] - x[0]);
        L = 1 - V;
        
        return true;
        
        // Решение уравнения Речфорда-Райса
    }
    
} // namespace MySpace::PhAn;