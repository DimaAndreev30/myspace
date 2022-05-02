#pragma once

#include "params.h"
#include "solution.h"

#include <phase_analysis/libs/properties/pure_substance.h>

#include <string>
#include <utility>


namespace NMySpace::NPhan::NEoS {
    
    // Класс, реализующий расчеты по кубическим УРС типа Ван-дер-Ваальса.
    class TCubicEoS {
    public:
        // Вычисление параметров УРС:
        TParams BuildParams(const TPureSubstanceProps& props, double T) const;
        TDimlessParamsFactory BuildDimlessParams(
            const TPureSubstanceProps& props, double T) const;
        
        // Вычисление давления через объем:
        double computeP(const TParams& p, double V) const;
        // Вычисление давления через объем и первой производной давления по объему:
        std::pair<double, double> computeDP(const TParams& p, double V) const;
        
        // Вычисление объема через давление (решение кубического уравнения):
        TSolution solve(const TDimlessParams& p) const;
        
    public:
        const std::string& getName() const {
            return Name_;
        }
        


        //{ Разные формулы:
        // Вычисление Z-factor:
        static double computeZFactor(double V, double T, double P);
        // Вычисление объема по Z-factor:
        static double computeFromZFactor(double Z, double T, double P);
        
        // Вычисление летучести фазы:
        // Параметры на входе должны быть в безразмерной форме.
        
        // Множитель в формуле летучести, одинаковый для каждой компоненты смеси:
        double computeM(const TParamsBase& params, double Z) const;
        // Вариация, принимающая на вход параметры в температурной форме:
        double computeM(const TParamsBase& params, double Z, double P) const;
        
        // Непосредственно вычисление летучести:
        static double getPhi(double Si, double A, double Bi, double B, double Z, double M);
        // Вариация, принимающая на вход параметры в температурной форме:
        static double getPhi(double Si, double A, double Bi, double B, double Z, double M, double P);
        
        //}
        
        
        
    protected:
        TCubicEoS(double m1, double m2,
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
        
    private:
        double computeDemoninator(const TParams& p, double V) const;
        double computePWith(const TParams& p, double V, double denom) const;
        double computeDPWith(const TParams& p, double V, double denom) const;
        
    private:
        double m1_, m2_;
        double a0_, b0_;
        
        std::string Name_;
    };
    
}
