#include "interface.h"

#include "constants.h"

#include <phase_analysis/libs/cubic_equation/simple.h>
#include <phase_analysis/libs/utils/easy_sort.h>

#include <limits>
#include <algorithm>


namespace MySpace::PhAn::EoS {
    
    Interface::Interface(double m1, double m2,
                         double a0, double b0,
                         const std::string& name)
        : m1_(m1), m2_(m2)
        , a0_(a0), b0_(b0)
        , name_(name)
        {
        }
        
    Params Interface::computeParams(const PureSubstanceProps& props,
                                    double T) const {
        double RT = R_CONST*props.Tc;
        double Tr = T/props.Tc;
                             
        return Params{
            .A = alpha(Tr, props.w)*RT*RT/props.Pc,
            .B = beta()*RT/props.Pc
        };
    }
                         
    Params Interface::computeParams(const PureSubstanceProps& props,
                                    double T, 
                                    double P) const {
        double Pr = P/props.Pc;
        double Tr = T/props.Tc;
                             
        return Params{
            .A = alpha(Tr, props.w)*Pr/(Tr*Tr),
            .B = beta()*Pr/Tr
        };
    }
                         
    Params Interface::computeParamsTFactor(const PureSubstanceProps& props,
                                           double T) const {
        double Tr = T/props.Tc;
                             
        return Params{
            .A = alpha(Tr, props.w)/(Tr*Tr*props.Pc),
            .B = beta()/(Tr*props.Pc)
        };
    }
    
    Params Interface::computeParamsFromTFactor(const Params& params,
                                               double P) {
        return Params{
            .A = params.A*P,
            .B = params.B*P
        };
    }
    
    double Interface::computeP(const Params& params, double T, double V) const {
        return R_CONST*T/(V - params.B) - 
               params.A/((V + m1_*params.B)*(V + m2_*params.B));
    }
    
    double Interface::computeDP(const Params& params, double T, double V) const {
        double denom = (V + m1_*params.B)*(V + m2_*params.B);
        return -R_CONST*T/((V - params.B)*(V - params.B)) + 
               params.A*(2*V + (m1_ + m2_)*params.B)/(denom*denom);
    }
    
    Solution extractSolution(CubicEquation::Solution solution, 
                             double bound,
                             bool isPPositive) {
        if (isPPositive) {
            if (solution.type == CubicEquation::Solution::ONE_ROOT) {
                if (solution.roots[0] > bound) {
                    return Solution(solution.roots[0]);
                } else {
                    return Solution(Solution::POSITIVE_P_NO_ROOTS);
                }
            } else {
                Utility::sort3(solution.roots.data());
                
                if (solution.roots[0] > bound) {
                    return Solution(solution.roots[0], solution.roots[2]);
                } else if (solution.roots[1] > bound) {
                    return Solution(solution.roots[1], solution.roots[2], 
                                    Solution::POSITIVE_P_TWO_ROOTS);
                } else if (solution.roots[2] > bound) {
                    return Solution(solution.roots[2]);
                } else {
                    return Solution(Solution::POSITIVE_P_NO_ROOTS);
                }
            }
        } else {
            if (solution.type == CubicEquation::Solution::ONE_ROOT) {
                if (solution.roots[0] < bound) {
                    return Solution(solution.roots[0], Solution::NEGATIVE_P_ONE_ROOT);
                } else {
                    return Solution();
                }
            } else {
                Utility::sort3Desc(solution.roots.data());
                
                if (solution.roots[0] < bound) {
                    return Solution(solution.roots[0], solution.roots[2], 
                                    Solution::NEGATIVE_P_THREE_ROOTS);
                } else if (solution.roots[1] < bound) {
                    return Solution(solution.roots[1]);
                } else if (solution.roots[2] < bound) {
                    return Solution(solution.roots[2], 
                                    Solution::NEGATIVE_P_ONE_ROOT);
                } else {
                    return Solution();
                }
            }
        }
    }
    
    Solution Interface::solve(const Params& params, bool isPPositive) const {
        return extractSolution(
            CubicEquation::solve(
                (m1_ + m2_ - 1)*params.B - 1,
                params.A - ((m1_ + m2_ - m1_*m2_)*params.B + (m1_ + m2_))*params.B,
                -(params.A + m1_*m2_*params.B*(params.B + 1))*params.B
            ),
            isPPositive ? std::max({params.B, -params.B*m1_, -params.B*m2_}) : 
                          std::min({params.B, -params.B*m1_, -params.B*m2_}),
            isPPositive
        );
    }
    
    double Interface::computeZFactor(double V, double T, double P) {
        return P*V/(R_CONST*T);
    }
    
    double Interface::computeFromZFactor(double Z, double T, double P) {
        return Z*R_CONST*T/P;
    }
    
} // namespace MySpace::PhAn::EoS;