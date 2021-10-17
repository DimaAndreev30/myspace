#include "solver.h"


namespace MySpace::PhAn {
    
    PhEqResult computePhEq(const PhEqSettings& setts, 
                           MixtureInterface& mixture,
                           const std::vector<double>& z, 
                           std::vector<double>& kValues) {
        int N = mixture.getN();
        
        TwoPhaseCompos compos(N);
        std::vector<double> phiL(N), phiV(N);
        
        int iterationsNumber = 0;
        while (iterationsNumber < setts.maxIterationsNumber) {
            ++iterationsNumber;
            
            if (!compos.setFromKValues(kValues, z)) {
                break;
            }
            
            if (mixture.setCompos(
                    compos.x, 
                    MixtureInterface::Traits::AS_LIQUID
                ) != MixtureInterface::Status::OK) {
                break;
            }
            
            for (int i = 0; i < N; i++) {
                phiL[i] = mixture.getPhi(i);
            }
            
            if (mixture.setCompos(
                    compos.y, 
                    MixtureInterface::Traits::AS_VAPOR
                ) != MixtureInterface::Status::OK) {
                break;
            }
            
            for (int i = 0; i < N; i++) {
                phiV[i] = mixture.getPhi(i);
            }
            
            double relerr = 0;
            for (int i = 0; i < N; i++) {
                kValues[i] = phiL[i]/phiV[i];
                relerr += compos.x[i]*kValues[i]/compos.y[i] - 1.0;
            }
            
            if (relerr < setts.eps*N) {
                return PhEqResult{
                    .status = PhEqResult::OK,
                    .iterationsNumber = iterationsNumber,
                    .compos = compos
                };
            }
        }
        
        return PhEqResult{
            .status = PhEqResult::NOT_CONVERGE,
            .iterationsNumber = iterationsNumber
        };
    }
    
} // namespace MySpace::PhAn;