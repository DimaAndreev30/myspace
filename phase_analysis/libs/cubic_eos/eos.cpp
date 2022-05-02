#include "eos.h"

#include "constants.h"

#include <phase_analysis/libs/cubic_equation/simple.h>
#include <phase_analysis/libs/utils/easy_sort.h>

#include <algorithm>
#include <cmath>
#include <iostream>


namespace NMySpace::NPhan::NEoS {
    
    TCubicEoS::TCubicEoS(double m1, double m2,
                         double a0, double b0,
                         const std::string& name)
        : m1_(m1), m2_(m2)
        , a0_(a0), b0_(b0)
        , Name_(name)
        {
        }
        
    TParams TCubicEoS::BuildParams(
        const TPureSubstanceProps& props,
        double T
    ) const {
        double RT = R_CONST*props.Tc;
        double Tr = T/props.Tc;
                             
        return TParamsBase{
            .T = T,
            .A = alpha(Tr, props.w)*RT*RT/props.Pc,
            .B = beta()*RT/props.Pc,
        };
    }
    
    TDimlessParamsFactory TCubicEoS::BuildDimlessParams(
        const TPureSubstanceProps& props,
        double T
    ) const {
        double Tr = T/props.Tc;
                             
        return TParamsBase{
            .T = T,
            .A = alpha(Tr, props.w)/(Tr*Tr*props.Pc),
            .B = beta()/(Tr*props.Pc),
        };
    }
    
    double TCubicEoS::computeDemoninator(const TParams& p, double V) const {
        return (V + m1_*p.B)*(V + m2_*p.B);
    }
    
    double TCubicEoS::computePWith(const TParams& p, double V, double denom) const {
        return R_CONST*p.T/(V - p.B) - p.A/denom;
    }
    
    double TCubicEoS::computeDPWith(const TParams& p, double V, double denom) const {
        double shift = V - p.B;
        return -R_CONST*p.T/(shift*shift) + p.A*(2*V + (m1_ + m2_)*p.B)/(denom*denom);
    }
    
    double TCubicEoS::computeP(const TParams& p, double V) const {
        return computePWith(p, V, computeDemoninator(p, V));
    }
    
    std::pair<double, double> TCubicEoS::computeDP(const TParams& p, double V) const {
        double denom = computeDemoninator(p, V);
        return {
            computePWith(p, V, denom),
            computeDPWith(p, V, denom),
        };
    }
    
    static TSolution extractSolution(
        NCubicEq::TSolution s, 
        double bound,
        bool isPPositive
    ) {
        if (isPPositive) {
            if (s.Type == NCubicEq::TSolution::EType::One) {
                return TSolution(s.Im.Real > bound ? s.Im.Real : bound);
            } else {
                NUtils::sort3(s.At.data());
                if (s.At[1] > bound) {
                    return TSolution(s.At[0] > bound ? s.At[0] : bound, s.At[2]);
                }
                return TSolution(s.At[2] > bound ? s.At[2] : bound);
            }
        } else {
            if (s.Type == NCubicEq::TSolution::EType::One) {
                return TSolution();
            } else {
                NUtils::sort3Desc(s.At.data());
                return TSolution(s.At[1] < bound ? s.At[1] : bound);
            }
        }
    }
    
    TSolution TCubicEoS::solve(const TDimlessParams& p) const {
        return extractSolution(
            NCubicEq::simpleSolve(
                (m1_ + m2_ - 1)*p.B - 1,
                p.A - ((m1_ + m2_ - m1_*m2_)*p.B + (m1_ + m2_))*p.B,
                -(p.A + m1_*m2_*p.B*(p.B + 1))*p.B
            ),
            p.P > 0 ? std::max({p.B, -p.B*m1_, -p.B*m2_}) : 
                      std::min({p.B, -p.B*m1_, -p.B*m2_}),
            p.P > 0
        );
    }
    
    
    
    double TCubicEoS::computeZFactor(double V, double T, double P) {
        return P*V/(R_CONST*T);
    }
    
    double TCubicEoS::computeFromZFactor(double Z, double T, double P) {
        return Z*R_CONST*T/P;
    }
    
    double TCubicEoS::computeM(const TParamsBase& params, double Z) const {
        return params.A*std::log((Z + m2_*params.B)/(Z + m1_*params.B))/((m1_ - m2_)*params.B);
    }
    
    double TCubicEoS::computeM(const TParamsBase& params, double Z, double P) const {
        return computeM(params, Z/P);
    }
    
    double TCubicEoS::getPhi(double Si, double A, double Bi, double B, double Z, double M) {
        return std::exp(Bi*(Z - 1)/B + (2*Si/A - Bi/B)*M)/(Z - B);
    }
    
    double TCubicEoS::getPhi(double Si, double A, double Bi, double B, double Z, double M, double P) {
        return std::exp(Bi*(Z - 1)/B + (2*Si/A - Bi/B)*M)/(Z - B*P);
    }
        
    
}
