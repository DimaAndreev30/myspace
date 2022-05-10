#include "plot_by_P.h"

#include <phase_analysis/libs/cubic_eos/constants.h>

#include <libs/utils/assert.h>

#include <cmath>


namespace NMySpace::NPhan {
    
    void CreatePVCurveByP(std::ostream& out,
                          const NCubicEoS::TDimlessParamsWOPressure& p,
                          const NCubicEoS::TCubicEoS& eos,
                          double T,
                          int N, double P1, double P2) {
        MS_ENSURE(N > 1, "N should be > 1: got " << N << " <= 1");
        MS_ENSURE(P1 < P2, "P1 should be < P2: got " << P1 << " >= " << P2);
        
        double dP = (P2 - P1)/(N - 1);
        MS_ENSURE(
            dP > 1e-150 && std::abs(dP/P1) > 1e-12 && std::abs(dP/P2) > 1e-12,
            "N is too big: got " << N);
        
        double twoPhaseStart;
        enum {
            NoTwoPhasesDetected,
            TwoPhasesLiquid,
            TwoPhasesVapor
        } state = NoTwoPhasesDetected;
        
        auto switchPhase = [&]() mutable {
            out << "\n\n";
            
            state = TwoPhasesVapor;
            P2 = twoPhaseStart;
            P1 = 0;
        };
        
        while(true) {
            if (P2 <= P1) {
                switch (state) {
                    case NoTwoPhasesDetected:
                    case TwoPhasesVapor:
                        return;
                    case TwoPhasesLiquid:
                        switchPhase();
                        continue;
                }
            }
                
            NCubicEoS::TSolution solution = eos.Solve(p, P2);
            
            double Z;
            switch (state) {
                case NoTwoPhasesDetected:
                    if (!solution.IsSolution()) {
                        continue;
                    }
                    if (solution.IsTwoPhases()) {
                        state = TwoPhasesLiquid;
                        twoPhaseStart = P2;
                    }
                    Z = solution.GetLiquid();
                    break;
                case TwoPhasesLiquid:
                    if (!solution.IsSolution() ||
                        (!solution.IsTwoPhases() && P2 > dP)) {
                        switchPhase();
                        continue;
                    }
                    Z = solution.GetLiquid();
                    break;
                case TwoPhasesVapor:
                    if (!solution.IsSolution()) {
                        return;
                    }
                    Z = solution.GetVapor();
                    break;
            }
            
            out << P2 << ' ' << Z << ' ' 
                << NCubicEoS::FromZFactor(Z, P2, T) << ' ' 
                << (solution.IsTwoPhases() ? "two phases" : "one phase") << '\n';
                
            P2 -= dP;
        }
    }
                          
    void CreatePVCurveByP(std::ostream& out,
                          const TPureSubstanceProps& props,
                          const NCubicEoS::TCubicEoS& eos,
                          double T,
                          int N, double P1, double P2) {
        CreatePVCurveByP(out, 
                         eos.BuildDimlessParams(props, T),
                         eos,
                         T,
                         N, P1, P2);
    }
    
}
