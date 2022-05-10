#pragma once

#include <phase_analysis/libs/cubic_eos/eos.h>
#include <phase_analysis/libs/cubic_eos/params.h>
#include <phase_analysis/libs/phase_equilibrium/mixture.h>
#include <phase_analysis/libs/properties/pure_substance.h>

#include <memory>
#include <vector>
#include <optional>


namespace NMySpace::NPhan {
    
    // TODO: Переделать способ хранение констант фазового равновесия
    // TODO: Валидировать входные данные
    
    class TCubicEoSMixtureFactory: public NPheq::IMixtureFactory {
    public:
        TCubicEoSMixtureFactory(
            const std::shared_ptr<NCubicEoS::TCubicEoS>& eos, 
            const std::vector<TPureSubstanceProps>& comps,
            double T,
            const std::vector<std::vector<double>>& k,
            std::optional<double> P = {});
            
        void SetPressure(double P);
        
    public:
        std::unique_ptr<NPheq::IMixture> Build(
            double P, 
            const std::vector<double>& c,
            ETrait trait) const;
            
        std::unique_ptr<NPheq::IMixture> Build(
            const std::vector<double>& c, 
            ETrait trait) const override;
        
    private:
        static std::vector<NCubicEoS::TDimlessParamsWOPressure> MakeParams(
            const std::shared_ptr<NCubicEoS::TCubicEoS>& eos, 
            const std::vector<TPureSubstanceProps>& comps,
            double T);
            
    public:
        mutable double ZL, ZV;
        
    private:
        const std::shared_ptr<NCubicEoS::TCubicEoS> EoS_;
        const std::vector<NCubicEoS::TDimlessParamsWOPressure> ParamsFactory_;
        const std::vector<std::vector<double>>& k_;
        
        std::optional<double> P_ = {};
    };

}
