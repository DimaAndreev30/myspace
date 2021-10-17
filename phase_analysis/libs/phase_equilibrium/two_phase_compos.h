#pragma once

#include <vector>


namespace MySpace::PhAn {
    
    // TODO: убрать обращение с данными напрямую - сделать сеттеры/геттеры
    class TwoPhaseCompos {
    public:
        double L, V; // Доля жидкой и газовой фаз (L + V = 1)
        
        std::vector<double> x; // Концентрации в жидкой фазе
        std::vector<double> y; // Концентрации в газовой фазе
        
    public:
        explicit TwoPhaseCompos(size_t N = 0);
        
    public:
        bool setFromKValues(const std::vector<double>& kValues, 
                            const std::vector<double>& z);
    };
    
} // namespace MySpace::PhAn;