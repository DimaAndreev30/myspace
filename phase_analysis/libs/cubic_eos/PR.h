#pragma once

#include "eos.h"


namespace NMySpace::NPhan::NEoS {
    
    // Уравнение Пенга-Робинсона.
    class TPR: public TCubicEoS {
    public:
        TPR();
        
    private:
        double AlphaT(double Tr, double w) const override;
    };
    
}
