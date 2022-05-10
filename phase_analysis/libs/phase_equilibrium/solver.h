#pragma once

#include "compos.h"
#include "mixture.h"

#include <vector>


namespace NMySpace::NPhan::NPheq {
    
    // TODO: Добавить валидации и проверок
    
    class TFlash {
    public:
        struct TSettings {
            size_t MaxIterationsNumber = 1000;
            double Eps = 1e-4;
        };
    
        struct TResult {
            enum EStatus {
                Ok,
                NotConverge
            } Status = Ok;
            
            size_t IterationsNumber = 0;
            
            TCompos Compos;
        };
        
        // Основной алгоритм, вычисляющий K-values и концентрации компонент в фазах
        // итерационным (flash) методом.
        static TResult Compute(
            const TSettings& setts, 
            const IMixtureFactory& mixtureFactory,
            const std::vector<double>& z, 
            std::vector<double>& kValues);
    };
    
    
    
     
}
