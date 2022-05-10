#pragma once

#include "params.h"
#include "solution.h"

#include <phase_analysis/libs/properties/pure_substance.h>

#include <cmath>
#include <string>
#include <utility>


namespace NMySpace::NPhan::NCubicEoS {
    
    // Класс, реализующий расчеты по кубическим УРС типа Ван-дер-Ваальса.
    class TCubicEoS {
    public:
        // Вычисление параметров УРС:
        TParams BuildParams(const TPureSubstanceProps& props, double T) const;
        TDimlessParams BuildDimlessParams(const TPureSubstanceProps& props, double T, double P) const;
        TDimlessParamsWOPressure BuildDimlessParams(const TPureSubstanceProps& props, double T) const;
        
        // Вычисление давления через объем:
        double ComputeP(const TParams& p, double T, double V) const;
        // Вычисление первой производной давления по объему:
        double ComputeDP(const TParams& p, double T, double V) const;
        // Вычисление давления через объем и первой производной давления по объему:
        std::pair<double, double> ComputePDP(const TParams& p, double T, double V) const;
        
        // Вычисление объема через давление (решение кубического уравнения):
        TSolution Solve(const TDimlessParams& p, double P) const;
        TSolution Solve(const TDimlessParamsWOPressure& p, double P) const;
        
        // Правило смешивания:
        template<class T>
        static TMixtureParams<T> ApplyMixtureRule(
            const std::vector<T>& p,
            const std::vector<double>& c,
            const std::vector<std::vector<double>>& k
        ) {
            double A = 0.0;
            double B = 0.0;
            std::vector<double> S(p.size(), 0);
            for (size_t i = 0; i < p.size(); ++i) {
                for (int j = 0; j < p.size(); j++) {
                    S[i] += c[j]*std::sqrt(p[i].A*p[j].A)*(1 - k[i][j]);
                }
                
                A += c[i]*S[i];
                B += c[i]*p[i].B;
            }
            
            return TMixtureParams<T>{
                .Params = TParamsBase{
                    .A = A,
                    .B = B,
                },
                .S = std::move(S),
            };
        }
        
        // Вычисление летучести:
        // Множитель в формуле летучести, одинаковый для каждой компоненты смеси:
        double ComputeM(const TDimlessParams& p, double Z) const;
        double ComputeM(const TDimlessParamsWOPressure& p, double Z, double P) const;
        // Сама летучесть:
        static double ComputePhi(
            size_t i,
            const TDimlessMixtureParams& mixtureParams,
            const std::vector<TDimlessParams>& componentParams,
            double Z, double M);
        static double ComputePhi(
            const TDimlessParams& mixtureParams, double S,
            const TDimlessParams& componentParams,
            double Z, double M);
        static double ComputePhi(
            size_t i,
            const TDimlessMixtureParamsWOPressure& mixtureParams,
            const std::vector<TDimlessParamsWOPressure>& componentParams,
            double Z, double M, double P);
        static double ComputePhi(
            const TDimlessParamsWOPressure& mixtureParams, double S,
            const TDimlessParamsWOPressure& componentParams,
            double Z, double M, double P);
        
    public:
        const std::string& GetName() const {
            return Name_;
        }
        
    protected:
        TCubicEoS(double m1, double m2,
                  double a0, double b0,
                  const std::string& name = "unknown");
        virtual ~TCubicEoS() = default;
        
    protected:
        virtual double AlphaT(double Tr, double w) const = 0;
        virtual double BetaT(double Tr) const {
            return 1.0;
        }
        
        double Alpha(double Tr, double w) const {
            return a0_*AlphaT(Tr, w);
        }
        double Beta(/*double Tr*/) const {
            return b0_; // *BetaT(Tr);
        }
        
    private:
        double ComputeDemoninator(double B, double V) const;
        double ComputeP(double A, double B, double T, double V, double denom) const;
        double ComputeDP(double A, double B, double T, double V, double denom) const;
        
        double ComputeM(double A, double B, double Z) const;
        double ComputeM(double A, double B, double Z, double P) const;
        static double ComputePhi(double A, double B, double Si, double Bi, double Z, double M);
        static double ComputePhi(double A, double B, double Si, double Bi, double Z, double M, double P);
        
    private:
        const double m1_, m2_;
        const double a0_, b0_;
        
        const std::string Name_;
    };
    
}
