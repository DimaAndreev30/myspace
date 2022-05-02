#pragma once

#include <string>

        
namespace NMySpace::NPhan::NEoS {
    
    class TSolution {
    public:
        TSolution()
            : IsTwoPhases_(false)
            , IsSolution_(false)
        {
        }
        
        TSolution(double solution)
            : Smaller_(solution)
            , Bigger_(solution)
            , IsTwoPhases_(false)
            , IsSolution_(true)
        {
        }
        
        TSolution(double smaller, double bigger)
            : Smaller_(smaller)
            , Bigger_(bigger)
            , IsTwoPhases_(true)
            , IsSolution_(true)
        {
        }
            
        bool IsSolution() const {
            return IsSolution_;
        }
        
        bool IsTwoPhases() const {
            return IsTwoPhases_;
        }
        
        double GetLiquid() const {
            return Smaller_;
        }
        
        double GetVapor() const {
            return Bigger_;
        }
        
    private:
        double Smaller_, Bigger_;
        bool IsTwoPhases_;
        bool IsSolution_;
    };
    
}
