#pragma once

#include <vector>


namespace NMySpace::NPhan::NPheq {
    
    class TCompos {
    public:
        double L, V; // Доля жидкой и газовой фаз (L + V = 1)
        
        std::vector<double> x; // Концентрации в жидкой фазе
        std::vector<double> y; // Концентрации в газовой фазе
        
    public:
        explicit TCompos(size_t N = 0);
        
    public:
        bool SetFromKValues(const std::vector<double>& kValues, 
                            const std::vector<double>& z);
    };
    
}
