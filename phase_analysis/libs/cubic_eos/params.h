#pragma once

#include <vector>
#include <type_traits>

// TODO: настроить себе нормальное окружение с --std=c++20
// и привести это место в порядок (сейчас неудобная инициализация производных классов)

namespace NMySpace::NPhan::NCubicEoS {
    
    // Структура для хранения параметров:
    struct TParamsBase {
        double A = 0.0;
        double B = 0.0;
    };
    
    // Параметры УРС в обычной форме:
    struct TParams: public TParamsBase {
        TParams(const TParamsBase& base = {})
            : TParamsBase(base) 
        {}
    };
    
    // Параметры УРС в безразмерной форме:
    struct TDimlessParams: public TParamsBase {
        TDimlessParams(const TParamsBase& base = {})
            : TParamsBase(base)
        {}
    };
    
    // Безразмерные параметры линейно зависят от давления, 
    // а потому можно вынести отдельно зависимость от температуры:
    // TDimlessParams(P, T) = P*TDimlessParamsWOPressure(T)
    struct TDimlessParamsWOPressure: public TParamsBase {
        TDimlessParamsWOPressure(const TParamsBase& base = {})
            : TParamsBase(base) 
        {}
        
        TDimlessParams With(double P) const;
    };
    
    template<class T = TParams>
    struct TMixtureParams {
        static_assert(std::is_base_of<TParamsBase, T>::value, "");
        
        T Params;
        std::vector<double> S;
    };
    using TDimlessMixtureParams = TMixtureParams<TDimlessParams>;
    using TDimlessMixtureParamsWOPressure = TMixtureParams<TDimlessParamsWOPressure>;
    
}
