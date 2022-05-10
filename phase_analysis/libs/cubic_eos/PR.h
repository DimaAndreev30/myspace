#pragma once

#include "eos.h"


namespace NMySpace::NPhan::NCubicEoS {
    
    // Уравнение Пенга-Робинсона.
    class TPR: public TCubicEoS {
    public:
        TPR();
        
    private:
        double AlphaT(double Tr, double w) const override;
    };
    
}
