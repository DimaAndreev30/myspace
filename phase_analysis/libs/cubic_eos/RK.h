#pragma once

#include "interface.h"


namespace MySpace::PhAn::EoS {
    
    // Уравнение Редлиха-Квонга.
    class RKInterface : public Interface {
    public:
        RKInterface();
        
    private:
        double alphaT(double Tr, double w) const override;
    };
    
} // namespace MySpace::PhAn::EoS;
