#include "plot_by_V.h"

#include <phase_analysis/libs/cubic_eos/constants.h>

#include <libs/utils/assert.h>

#include <cmath>


namespace NMySpace::NPhan {
    
    void CreatePVCurveByV(std::ostream& out,
                          const NCubicEoS::TParams& p,
                          const NCubicEoS::TCubicEoS& eos,
                          double T,
                          int N, bool isAuto, double V1, double V2) {
        MS_ENSURE(N > 1, "N should be > 1: got " << N << " <= 1");
        
        double po1, po2;
        
        if (isAuto) {
            po1 = 1/(p.B*1.0001);
            po2 = po1/(N + 1);
        } else {
            MS_ENSURE(V1 < V2, "V1 should be < V2: got " << V1 << " >= " << V2);
            
            po1 = 1/V1;
            po2 = 1/V2;
        }
        
        double dpo = (po1 - po2)/(N - 1);
        MS_ENSURE(
            dpo > 1e-150 && std::abs(dpo/po1) > 1e-12 && std::abs(dpo/po2) > 1e-12,
            "N is too big: got " << N);
        
        for (; po1 >= po2; po1 -= dpo) {
            double V = 1/po1;
            auto [P, DP] = eos.ComputePDP(p, T, V);
            
            out << V << ' ' << P << ' ' << DP << ' '
                << NCubicEoS::ToZFactor(V, P, T) << ' ' << po1 << '\n';
        }
    }
                          
    void CreatePVCurveByV(std::ostream& out,
                          const TPureSubstanceProps& props,
                          const NCubicEoS::TCubicEoS& eos,
                          double T,
                          int N, bool isAuto, double V1, double V2) {
        CreatePVCurveByV(out,
                         eos.BuildParams(props, T),
                         eos,
                         T,
                         N, isAuto, V1, V2);
    }
    
}
