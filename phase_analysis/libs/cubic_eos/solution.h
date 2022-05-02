#pragma once

#include <string>


        enum EStatus {
            Ok,
            PositivePressureNoRoots,
            PositivePressureTwoRoots,
            NegativePressureOneRoot,
            NegativePressureThreeRoots
        };
        
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
            
        bool isSolution() const {
            return IsSolution_;
        }
        
        bool isTwoPhases() const {
            return IsTwoPhases_;
        }
        
        double getL() const {
            return Smaller_;
        }
        
        double getV() const {
            return Bigger_;
        }
        
    private:
        double Smaller_, Bigger_;
        bool IsTwoPhases_;
        bool IsSolution_;
    };
    
}
