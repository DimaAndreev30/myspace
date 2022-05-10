#include "eos.h"

#include "constants.h"

#include <phase_analysis/libs/cubic_equation/simple.h>
#include <phase_analysis/libs/utils/easy_sort.h>

#include <algorithm>
#include <cmath>
#include <iostream>


namespace NMySpace::NPhan::NCubicEoS {
    
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
            .A = Alpha(Tr, props.w)*RT*RT/props.Pc,
            .B = Beta()*RT/props.Pc,
        };
    }
    
    TDimlessParams TCubicEoS::BuildDimlessParams(
        const TPureSubstanceProps& props, 
        double T, 
        double P
    ) const {
        return BuildDimlessParams(props, T).With(P);
    }
    
    TDimlessParamsWOPressure TCubicEoS::BuildDimlessParams(
        const TPureSubstanceProps& props,
        double T
    ) const {
        double Tr = T/props.Tc;
                             
        return TParamsBase{
            .A = Alpha(Tr, props.w)/(Tr*Tr*props.Pc),
            .B = Beta()/(Tr*props.Pc),
        };
    }
    
    
    double TCubicEoS::ComputeDemoninator(double B, double V) const {
        return (V + m1_*B)*(V + m2_*B);
    }
    
    double TCubicEoS::ComputeP(double A, double B, double T, double V, double denom) const {
        return R_CONST*T/(V - B) - A/denom;
    }
    
    double TCubicEoS::ComputeDP(double A, double B, double T, double V, double denom) const {
        double shift = V - B;
        return -R_CONST*T/(shift*shift) + A*(2*V + (m1_ + m2_)*B)/(denom*denom);
    }
    
    double TCubicEoS::ComputeP(const TParams& p, double T, double V) const {
        return ComputeP(p.A, p.B, T, V, ComputeDemoninator(p.B, V));
    }
    
    double TCubicEoS::ComputeDP(const TParams& p, double T, double V) const {
        return ComputeDP(p.A, p.B, T, V, ComputeDemoninator(p.B, V));
    }
    
    std::pair<double, double> TCubicEoS::ComputePDP(const TParams& p, double T, double V) const {
        double denom = ComputeDemoninator(p.B, V);
        return {
            ComputeP(p.A, p.B, T, V, denom),
            ComputeDP(p.A, p.B, T, V, denom),
        };
    }
    
    
    static TSolution ExtractSolution(
        NCubicEq::TSolution s, 
        double bound,
        bool isPPositive
    ) {
        if (isPPositive) {
            if (s.Type == NCubicEq::TSolution::EType::One) {
                return TSolution(s.Im.Real > bound ? s.Im.Real : bound);
            } else {
                NUtils::Sort3(s.At.data());
                if (s.At[1] > bound) {
                    return TSolution(s.At[0] > bound ? s.At[0] : bound, s.At[2]);
                }
                return TSolution(s.At[2] > bound ? s.At[2] : bound);
            }
        } else {
            if (s.Type == NCubicEq::TSolution::EType::One) {
                return TSolution();
            } else {
                NUtils::Sort3Desc(s.At.data());
                return TSolution(s.At[1] < bound ? s.At[1] : bound);
            }
        }
    }
    
    TSolution TCubicEoS::Solve(const TDimlessParams& p, double P) const {
        return ExtractSolution(
            NCubicEq::SimpleSolve(
                (m1_ + m2_ - 1)*p.B - 1,
                p.A - ((m1_ + m2_ - m1_*m2_)*p.B + (m1_ + m2_))*p.B,
                -(p.A + m1_*m2_*p.B*(p.B + 1))*p.B
            ),
            P > 0 ? std::max({p.B, -p.B*m1_, -p.B*m2_}) : 
                    std::min({p.B, -p.B*m1_, -p.B*m2_}),
            P > 0
        );
    }
    
    TSolution TCubicEoS::Solve(const TDimlessParamsWOPressure& p, double P) const {
        return Solve(p.With(P), P);
    }
    
    
    double TCubicEoS::ComputeM(double A, double B, double Z) const {
        return A*std::log((Z + m2_*B)/(Z + m1_*B))/((m1_ - m2_)*B);
    }
    
    double TCubicEoS::ComputeM(double A, double B, double Z, double P) const {
        return ComputeM(A, B, Z/P);
    }
    
    double TCubicEoS::ComputeM(const TDimlessParams& p, double Z) const {
        return ComputeM(p.A, p.B, Z);
    }
    
    double TCubicEoS::ComputeM(const TDimlessParamsWOPressure& p, double Z, double P) const {
        return ComputeM(p.A, p.B, Z, P);
    }
    
    double TCubicEoS::ComputePhi(double A, double B, double Si, double Bi, double Z, double M) {
        return std::exp(Bi*(Z - 1)/B + (2*Si/A - Bi/B)*M)/(Z - B);
    }
    
    double TCubicEoS::ComputePhi(double A, double B, double Si, double Bi, double Z, double M, double P) {
        return std::exp(Bi*(Z - 1)/B + (2*Si/A - Bi/B)*M)/(Z - B*P);
    }
    
    double TCubicEoS::ComputePhi(
        size_t i,
        const TDimlessMixtureParams& mixtureParams,
        const std::vector<TDimlessParams>& componentParams,
        double Z, double M
    ) {
        return ComputePhi(
            mixtureParams.Params, mixtureParams.S[i],
            componentParams[i],
            Z, M);
    }
    
    double TCubicEoS::ComputePhi(
        const TDimlessParams& mixtureParams, double S,
        const TDimlessParams& componentParams,
        double Z, double M
    ) {
        return ComputePhi(mixtureParams.A, mixtureParams.B, S, componentParams.B, Z, M);
    }
    
    double TCubicEoS::ComputePhi(
        size_t i,
        const TDimlessMixtureParamsWOPressure& mixtureParams,
        const std::vector<TDimlessParamsWOPressure>& componentParams,
        double Z, double M, double P
    ) {
        return ComputePhi(
            mixtureParams.Params, mixtureParams.S[i],
            componentParams[i],
            Z, M, P);
    }
    
    double TCubicEoS::ComputePhi(
        const TDimlessParamsWOPressure& mixtureParams, double S,
        const TDimlessParamsWOPressure& componentParams,
        double Z, double M, double P
    ) {
        return ComputePhi(mixtureParams.A, mixtureParams.B, S, componentParams.B, Z, M, P);
    }
    
}
