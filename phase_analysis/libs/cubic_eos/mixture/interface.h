#pragma once

#include <phase_analysis/libs/cubic_eos/params.h>
#include <phase_analysis/libs/cubic_eos/interface.h>
#include <phase_analysis/libs/properties/pure_substance.h>
#include <phase_analysis/libs/mixture/interface.h>

#include <vector>
#include <memory>


namespace MySpace::PhAn::EoS {

    // TODO:
    // - Вынести правило смешивания и хранения параметров в отдельные классы
    // - Разделить зависящие и не зависящие от молярного состава параметры и
    // реализовать возможность работать сразу с несколькими молярными составами.
    // - Реализовать специальный класс, обеспечивающий значения 
    // коэффициентов парного взаимодействия. Пока же это дело сделано криво.
    
    // Класс для вычисления термодинамических параметров смеси.
    // Класс одноразовый: для новых температуры/УРС/компонентного состава 
    // нужно создавать отдельный экземпляр.
    class CubicEoSMixture : public MixtureInterface {
    public:
        CubicEoSMixture(double T, const std::shared_ptr<Interface>& eos, int N = 0);
    
    public:
        int getN() const override;
        Status setCompos(const std::vector<double>& c, Traits trait) override;
        double getPhi(int i) const override;
        
        void addComponent(const PureSubstanceProps& props);
        void setK(const std::shared_ptr<std::vector<std::vector<double>>>& k);
        void setPressure(double P);
        
        Params getMixtureParams() const;
        
    public:
        // Костыль, который, я надеюсь, уйдет позже, 
        // когда я сделаю возможность работать с несколькими молярными составами.
        double ZL, ZV;
        
    private:
        double T_, P_;
        
        std::shared_ptr<Interface> eos_;
        std::shared_ptr<std::vector<std::vector<double>>> k_;
        
        std::vector<Params> params_;
        std::vector<double> S_;
        Params mixtureParams_;
        
        double Z_, M_;
    };

} // namespace MySpace::PhAn::EoS;
