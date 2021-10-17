#pragma once

#include "params.h"
#include "solution.h"

#include <phase_analysis/libs/properties/pure_substance.h>

#include <string>


// TODO: переименовать Interface в CubicEoS

namespace MySpace::PhAn::EoS {
    
    // Класс, реализующий расчеты по кубическим УРС типа Ван-дер-Ваальса.
    // Содержит зависящие от УРС и просто связанные с ними формулы.
    class Interface {
    protected:
        Interface(double m1, double m2,
                  double a0, double b0,
                  const std::string& name = "unknown");
        
    protected:
        virtual double alphaT(double Tr, double w) const = 0;
        virtual double betaT(double Tr) const {
            return 1.0;
        }
        
        double alpha(double Tr, double w) const {
            return a0_*alphaT(Tr, w);
        }
        double beta(/*double Tr*/) const {
            return b0_; // *betaT(Tr);
        }
        
    public:
        //{ Вычисление параметров УРС:
        // В обычной форме:
        Params computeParams(const PureSubstanceProps& props,
                             double T) const;
        // В безразмерной форме:
        Params computeParams(const PureSubstanceProps& props,
                             double T, 
                             double P) const;
        // Вычисляет составляющую безразмерной формы, зависящую от температуры: 
        // A(T), B(T), где A(T, P) = A(T)*P, B(T, P) = B(T)*P
        // (далее буду называть это температурной формой)
        Params computeParamsTForm(const PureSubstanceProps& props,
                                  double T) const;
        // Вычисляет параметры в безразмерной форме из температурной формы:
        // (банальное домножение на P, можно делать это и без помощи функции)
        static Params computeParamsFromTForm(const Params& params, double P);
        //}
        
        //{ Вычисление давления по УРС:
        // Параметры на входе должны быть в обычной (размерной) форме.
        // Давление через объем:
        double computeP(const Params& params, double T, double V) const;
        // Производная давления по объему через объем:
        double computeDP(const Params& params, double T, double V) const;
        //}
        
        //{ Вычисление объема по УРС (решение кубического уравнения):
        // Параметры на входе должны быть в безразмерной форме.
        // Результат так же в безразмерной форме (Z-factor)
        Solution solve(const Params& params, bool isPPositive = true) const;
        // Вариация, принимающая на вход параметры в температурной форме:
        Solution solve(const Params& params, double P) const;
        //}
        
        //{ Разные формулы:
        // Вычисление Z-factor:
        static double computeZFactor(double V, double T, double P);
        // Вычисление объема по Z-factor:
        static double computeFromZFactor(double Z, double T, double P);
        
        // Вычисление летучести фазы:
        // Параметры на входе должны быть в безразмерной форме.
        
        // Множитель в формуле летучести, одинаковый для каждой компоненты смеси:
        double computeM(const Params& params, double Z) const;
        // Вариация, принимающая на вход параметры в температурной форме:
        double computeM(const Params& params, double Z, double P) const;
        
        // Непосредственно вычисление летучести:
        static double getPhi(double Si, double A, double Bi, double B, double Z, double M);
        // Вариация, принимающая на вход параметры в температурной форме:
        static double getPhi(double Si, double A, double Bi, double B, double Z, double M, double P);
        
        //}
       
        const std::string& getName() const {
            return name_;
        }
        
    private:
        double m1_, m2_;
        double a0_, b0_;
        
        std::string name_;
    };
    
} // namespace MySpace::PhAn::EoS;