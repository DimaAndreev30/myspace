#pragma once

#include "eos.h"


namespace NMySpace::NPhan::NCubicEoS {
    
    // Уравнение Соуве-Редлиха-Квонга.
    class TSRK: public TCubicEoS {
    public:
        TSRK();
        
    private:
        double AlphaT(double Tr, double w) const override;
    };
    
}
