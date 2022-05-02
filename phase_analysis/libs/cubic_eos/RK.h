#pragma once

#include "eos.h"


namespace NMySpace::NPhan::NEoS {
    
    // Уравнение Редлиха-Квонга.
    class TRK : public TCubicEoS {
    public:
        TRK();
        
    private:
        double alphaT(double Tr, double w) const override;
    };
    
}
