#pragma once

#include "eos.h"


namespace NMySpace::NPhan::NCubicEoS {
    
    // Уравнение Редлиха-Квонга.
    class TRK: public TCubicEoS {
    public:
        TRK();
        
    private:
        double AlphaT(double Tr, double w) const override;
    };
    
}
