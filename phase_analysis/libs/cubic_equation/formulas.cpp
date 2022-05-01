#include "formulas.h"

#include <cmath>


namespace NMySpace::NPhan::NCubicEq {
    
    double getAlphaPlusBeta(double p, double q, double p3, double q2) {
        static const double DOUBLE_EPSILON12 = 1.0/0x1000;

        // Разложение в ряд тейлора по q2/p3 << 1.
        if (q2 <= -DOUBLE_EPSILON12*p3) {
            double h = -q2/p3;
            return 2*q*(1 - 4*(1 - 4*(1 - 16*h/27)*h/9)*h/27)/(3*p);
        }
        // Разложение в ряд тейлора по q2/p3 << 1.
        else if (std::abs(p3) <= DOUBLE_EPSILON12*q2) {
            double h = p3/q2;
            h = -h*(1 + (1 + (1 + (5/* + 7*h/2*/)*h/8)*h/2)*h/4)/2;
            return std::cbrt(q*h) - std::cbrt(q*(2 + h));
        }
        // Вычисление обычным способом.
        else {
            double sqrtQ = std::sqrt(q2 - p3);
            return std::cbrt(-q + sqrtQ) - std::cbrt(q + sqrtQ);
        }
    }
    
}
