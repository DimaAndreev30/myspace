#pragma once

#include "eos.h"


namespace NMySpace::NPhan::NEoS {
    
    // Уравнение Соуве-Редлиха-Квонга.
    class TSRK : public TCubicEoS {
    public:
        TSRK();
        
    private:
        double alphaT(double Tr, double w) const override;
    };
    
}
