#include "plot_by_V.h"

#include <libs/utils/assert.h>

#include <cmath>
#include <stdexcept>

using MySpace::Utility::MakeString;


namespace MySpace::PhAn {
    
    void createPVCurveByV(std::ostream& out,
                          const EoS::Params& params,
                          const EoS::Interface& eos,
                          double T,
                          int N, bool isAuto, double V1, double V2) {
        MS_ASSERT_EX(N > 1, 
                     std::invalid_argument, 
                     MakeString() << "N should be > 1: got " << N << " <= 1"
        );
        
        double po1, po2;
        
        if (isAuto) {
            po1 = 1/(params.B*1.0001);
            po2 = po1/(N + 1);
        } else {
            MS_ASSERT_EX(V1 < V2, 
                         std::invalid_argument, 
                         MakeString() << "V1 should be < V2: got " << V1 << " >= " << V2
            );
            
            po1 = 1/V1;
            po2 = 1/V2;
        }
        
        double dpo = (po1 - po2)/(N - 1);
        MS_ASSERT_EX(dpo > 1e-150 && std::abs(dpo/po1) > 1e-12 && std::abs(dpo/po2) > 1e-12,
                     std::invalid_argument,
                     MakeString() << "N is too big: got " << N 
        );
        
        for (; po1 >= po2; po1 -= dpo) {
            double V = 1/po1;
            double P = eos.computeP(params, T, V);
            double dP = eos.computeDP(params, T, V);
            
            out << V << ' ' << P << ' ' << dP << ' '
                << eos.computeZFactor(V, T, P) << ' ' << po1 << '\n';
        }
    }
                          
    void createPVCurveByV(std::ostream& out,
                          const PureSubstanceProps& props,
                          const EoS::Interface& eos,
                          double T,
                          int N, bool isAuto, double V1, double V2) {
        createPVCurveByV(out,
                         eos.computeParams(props, T),
                         eos,
                         T,
                         N, isAuto, V1, V2);
    }
    
} // namespace MySpace::PhAn;
