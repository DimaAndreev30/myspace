#include "mixture_factory.h"

#include <cmath>


namespace NMySpace::NPhan {

    TCubicEoSMixtureFactory::TCubicEoSMixtureFactory(
        const std::shared_ptr<NCubicEoS::TCubicEoS>& eos, 
        const std::vector<TPureSubstanceProps>& comps,
        double T,
        const std::vector<std::vector<double>>& k,
        std::optional<double> P
    )
        : IMixtureFactory(comps.size())
        , EoS_(eos)
        , ParamsFactory_(MakeParams(eos, comps, T))
        , k_(k)
        , P_(P)
    {
    }
    
    std::vector<NCubicEoS::TDimlessParamsWOPressure> TCubicEoSMixtureFactory::MakeParams(
        const std::shared_ptr<NCubicEoS::TCubicEoS>& eos, 
        const std::vector<TPureSubstanceProps>& comps,
        double T
    ) {
        std::vector<NCubicEoS::TDimlessParamsWOPressure> res;
        
        res.resize(comps.size());
        for (size_t i = 0; i < res.size(); ++i) {
            res[i] = eos->BuildDimlessParams(comps[i], T);
        }
        
        return res;
    }      

    void TCubicEoSMixtureFactory::SetPressure(double P) {
        P_ = P;
    }
    
    std::unique_ptr<NPheq::IMixture> TCubicEoSMixtureFactory::Build(
        double P, 
        const std::vector<double>& c,
        ETrait trait
    ) const {
        NCubicEoS::TDimlessMixtureParamsWOPressure mixture = 
            EoS_->ApplyMixtureRule(ParamsFactory_, c, k_);
        
        NCubicEoS::TSolution solution = EoS_->Solve(mixture.Params, P);
        
        double Z;
        switch (trait) {
        case ETrait::AsLiquid:
            ZL = Z = solution.GetLiquid();
            break;
        case ETrait::AsVapor:
            ZV = Z = solution.GetVapor();
            break;
        }
        
        double M = EoS_->ComputeM(mixture.Params, Z, P);
        
        std::vector<double> phi(ParamsFactory_.size());
        for (size_t i = 0; i < phi.size(); ++i) {
            phi[i] = EoS_->ComputePhi(i, mixture, ParamsFactory_, Z, M, P);
        }
        
        return std::make_unique<NPheq::TSimpleMixtureHolder>(std::move(phi));
    }
        
    std::unique_ptr<NPheq::IMixture> TCubicEoSMixtureFactory::Build(
        const std::vector<double>& c, 
        ETrait trait
    ) const {
        // TODO: Check P.has_value();
        return Build(*P_, c, trait);
    }

}
