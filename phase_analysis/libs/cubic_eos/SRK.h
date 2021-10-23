#pragma once

#include "interface.h"


namespace MySpace::PhAn::EoS {
    
    // Уравнение Соуве-Редлиха-Квонга.
    class SRKInterface : public Interface {
    public:
        SRKInterface();
        
    private:
        double alphaT(double Tr, double w) const override;
    };
    
} // namespace MySpace::PhAn::EoS;
