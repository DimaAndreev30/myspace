#include "simple.h"

#include "formulas.h"

#include <cmath>


namespace MySpace::PhAn::CubicEquation {

    Solution solve(double a, double b, double c) {
        a /= 3; b /= 3;
        
        // Вычисление коэффициентов приведенного уравнения:
        double p = a*a - b;
        double r = a*b - c;
        double q = a*p - r/2;
        double p3 = p*p*p, q2 = q*q;
        
        // Три действительных корня
        if (q2 <= p3) {
            double sqrt_p = std::sqrt(p);
            double phi = std::acos(-q/(p*sqrt_p))/3;
            
            return Solution{
                .type = Solution::THREE_ROOT,
                .roots = {
                    2*sqrt_p*std::cos(phi) - a,
                    2*sqrt_p*std::cos(phi + 2*M_PI/3) - a,
                    2*sqrt_p*std::cos(phi - 2*M_PI/3) - a
                }
            };
        }
        // Один действительный корень
        else {
            return Solution{
                .type = Solution::ONE_ROOT,
                .roots = {
                    getAlphaPlusBeta(p, q, p3, q2) - a
                }
            };
        }
    }

} // namespace MySpace::PhAn::CubicEquation;