#pragma once


namespace NMySpace::NPhan::NEoS {
    
    // Структура для хранения параметров:
    struct TParamsBase {
        double T = 0.0;
        
        double A = 0.0;
        double B = 0.0;
    };
    
    // Параметры УРС в обычной форме:
    struct TParams: public TParamsBase {
        TParams(const TParamsBase& base)
            : TParamsBase(base) 
        {}
    };
    
    // Параметры УРС в безразмерной форме:
    struct TDimlessParams: public TParamsBase {
        TDimlessParams(const TParamsBase& base, double initP)
            : TParamsBase(base)
            , P(initP)
        {}
        
        double P = 0.0;
    };
    
    struct TDimlessParamsFactory: public TParamsBase {
        TDimlessParamsFactory(const TParamsBase& base)
            : TParamsBase(base) 
        {}
        
        TDimlessParams Build(double P) const;
    };
    
}
