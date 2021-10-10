#pragma once

#include "interface.h"


namespace MySpace::PhAn::EoS {
    
    // Уравнение Пенга-Робинсона.
    class PRInterface : public Interface {
    public:
        PRInterface();
        
    private:
        double alphaT(double Tr, double w) const override;
    };
    
} // namespace MySpace::PhAn::EoS;