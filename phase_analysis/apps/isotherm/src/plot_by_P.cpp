#include "plot_by_P.h"

#include <libs/utils/assert.h>

#include <cmath>
#include <stdexcept>


namespace MySpace::PhAn {
    
    void createPVCurveByP(std::ostream& out,
                          const EoS::Params& TFactor,
                          const EoS::Interface& eos,
                          double T,
                          int N, double P1, double P2) {
        ASSERT_EX(N > 1, std::invalid_argument, "N should be > 1");
        ASSERT_EX(P1 < P2, std::invalid_argument, "P1 should be < P2");
        
        double dP = (P2 - P1)/(N - 1);
        ASSERT_EX(dP > 1e-150 && std::abs(dP/P1) > 1e-12 && std::abs(dP/P2) > 1e-12,
                  std::invalid_argument,
                  "N is too big"
        );
        
        double twoPhaseP = P2;
        enum {
            NO_TWO_PHASES_DETECTED,
            TWO_PHASES_LIQUID,
            TWO_PHASES_GAS
        } state;
        
        while (true) {
            EoS::Params params = eos.computeParamsFromTFactor(TFactor, P2);
            EoS::Solution solution = eos.solve(params, P2 > 0);
            
            double Z = solution.getL();
            
            if (state == NO_TWO_PHASES_DETECTED) {
                if (P2 <= P1) {
                    break;
                }
                if (solution.isTwoPhases()) {
                    state = TWO_PHASES_LIQUID;
                    twoPhaseP = P2;
                }
            }
            if (state == TWO_PHASES_LIQUID) {
                if (P2 <= P1 ||
                    !solution.isSolution() ||
                    (!solution.isTwoPhases() && P2 > dP)) {
                    state = TWO_PHASES_GAS;
                    if (P1 <= 0) {
                        P1 = 0;
                    }
                    P2 = twoPhaseP;
                    
                    out << "\n\n";
                    
                    continue;
                }
            }
            if (state == TWO_PHASES_GAS) {
                if (P2 <= P1) {
                    break;
                }
                
                Z = solution.getV();
            }
            
            if (!solution.isSolution()) {
                break;
            }
            
            out << P2 << ' ' << Z << ' ' 
                << eos.computeFromZFactor(Z, T, P2) << ' ' 
                << solution.getStatusAsString() << " | "
                << (solution.isTwoPhases() ? "two phases" : "one phase") << '\n';
                
            P2 -= dP;
        }
    }
                          
    void createPVCurveByP(std::ostream& out,
                          const PureSubstanceProps& props,
                          const EoS::Interface& eos,
                          double T,
                          int N, double P1, double P2) {
        createPVCurveByP(out, 
                         eos.computeParamsTFactor(props, T),
                         eos,
                         T,
                         N, P1, P2);
    }
    
} // namespace MySpace::PhAn;