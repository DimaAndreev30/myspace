#include "plot_by_P.h"

#include <phase_analysis/libs/cubic_eos/constants.h>

#include <libs/utils/assert.h>

#include <cmath>


namespace NMySpace::NPhan {
    
    void createPVCurveByP(std::ostream& out,
                          const NEoS::TDimlessParamsFactory& p,
                          const NEoS::TCubicEoS& eos,
                          double T,
                          int N, double P1, double P2) {
        MY_ENSURE(N > 1, "N should be > 1: got " << N << " <= 1");
        MY_ENSURE(P1 < P2, "P1 should be < P2: got " << P1 << " >= " << P2);
        
        double dP = (P2 - P1)/(N - 1);
        MY_ENSURE(
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
                
            NEoS::TSolution solution = eos.solve(p.get(P2));
            
            double Z;
            switch (state) {
                case NoTwoPhasesDetected:
                    if (!solution.isSolution()) {
                        continue;
                    }
                    if (solution.isTwoPhases()) {
                        state = TwoPhasesLiquid;
                        twoPhaseStart = P2;
                    }
                    Z = solution.getL();
                    break;
                case TwoPhasesLiquid:
                    if (!solution.isSolution() ||
                        (!solution.isTwoPhases() && P2 > dP)) {
                        switchPhase();
                        continue;
                    }
                    Z = solution.getL();
                    break;
                case TwoPhasesVapor:
                    if (!solution.isSolution()) {
                        return;
                    }
                    Z = solution.getV();
                    break;
            }
            
            out << P2 << ' ' << Z << ' ' 
                << NEoS::FromZFactor(Z, P2, T) << ' ' 
                << (solution.isTwoPhases() ? "two phases" : "one phase") << '\n';
                
            P2 -= dP;
        }
    }
                          
    void createPVCurveByP(std::ostream& out,
                          const TPureSubstanceProps& props,
                          const NEoS::TCubicEoS& eos,
                          double T,
                          int N, double P1, double P2) {
        createPVCurveByP(out, 
                         eos.BuildDimlessParams(props, T),
                         eos,
                         T,
                         N, P1, P2);
    }
    
}
