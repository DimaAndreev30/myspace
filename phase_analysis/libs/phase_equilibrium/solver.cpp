#include "solver.h"

#include <cmath>


namespace NMySpace::NPhan::NPheq {
    
    TFlash::TResult TFlash::Compute(
        const TSettings& setts, 
        const IMixtureFactory& mixtureFactory,
        const std::vector<double>& z, 
        std::vector<double>& kValues
    ) {
        size_t N = mixtureFactory.N();
        
        TCompos compos(N);
        
        size_t iterationsNumber = 0;
        while (iterationsNumber < setts.MaxIterationsNumber) {
            ++iterationsNumber;
            
            if (!compos.SetFromKValues(kValues, z)) {
                break;
            }
            
            auto liquid = mixtureFactory.Build(
                    compos.x, 
                    IMixtureFactory::ETrait::AsLiquid);
                    
            auto vapor = mixtureFactory.Build(
                    compos.y, 
                    IMixtureFactory::ETrait::AsVapor);
            
            double relerr = 0;
            for (size_t i = 0; i < N; ++i) {
                kValues[i] = liquid->Phi(i)/vapor->Phi(i);
                relerr += std::abs(compos.x[i]*kValues[i]/compos.y[i] - 1.0);
            }
            
            if (relerr < setts.Eps*N) {
                return TResult{
                    .Status = TResult::EStatus::Ok,
                    .IterationsNumber = iterationsNumber,
                    .Compos = std::move(compos)
                };
            }
        }
        
        return TResult{
            .Status = TResult::EStatus::NotConverge,
            .IterationsNumber = iterationsNumber
        };
    }
    
}
