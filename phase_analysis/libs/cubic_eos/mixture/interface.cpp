#include "interface.h"

#include <cmath>


namespace MySpace::PhAn::EoS {

    CubicEoSMixture::CubicEoSMixture(double T, const std::shared_ptr<Interface>& eos, int N)
        : T_(T)
        , eos_(eos)
    {
        params_.reserve(N);
        S_.reserve(N);
    }
    
    int CubicEoSMixture::getN() const {
        return params_.size();
    }
    
    CubicEoSMixture::Status CubicEoSMixture::setCompos(const std::vector<double>& c, Traits trait) {
        int N = getN();
        S_.resize(N);
        
        mixtureParams_.A = 0.0;
        mixtureParams_.B = 0.0;
        
        for (int i = 0; i < N; i++) {
            S_[i] = 0.0;
            for (int j = 0; j < N; j++) {
                S_[i] += c[j]*std::sqrt(params_[i].A*params_[j].A)*(1 - (*k_)[i][j]);
            }
            mixtureParams_.A += c[i]*S_[i];
            mixtureParams_.B += c[i]*params_[i].B;
        }
        
        if (mixtureParams_.B < 0) {
            return INCORRECT_COMPOS;
        }
        
        Solution solution = eos_->solve(mixtureParams_, P_);
        
        if (!solution.isOk()) {
            return EOS_ERROR;
        }
        
        switch (trait) {
            case MixtureInterface::Traits::AS_LIQUID:
                Z_ = solution.getL();
                ZL = Z_;
                break;
            case MixtureInterface::Traits::AS_VAPOR:
                Z_ = solution.getV();
                ZV = Z_;
                break;
        }
        
        M_ = eos_->computeM(mixtureParams_, Z_, P_);
        
        return OK;
    }
    
    double CubicEoSMixture::getPhi(int i) const {
        return eos_->getPhi(S_[i], mixtureParams_.A, params_[i].B, mixtureParams_.B, Z_, M_, P_);
    }
    
    void CubicEoSMixture::addComponent(const PureSubstanceProps& props) {
        params_.push_back(eos_->computeParamsTForm(props, T_));
    }
    
    void CubicEoSMixture::setK(const std::shared_ptr<std::vector<std::vector<double>>>& k) {
        k_ = k;
    }
    
    void CubicEoSMixture::setPressure(double P) {
        P_ = P;
    }
    
    Params CubicEoSMixture::getMixtureParams() const {
        return eos_->computeParamsFromTForm(mixtureParams_, P_);
    }
    

} // namespace MySpace::PhAn::EoS;
