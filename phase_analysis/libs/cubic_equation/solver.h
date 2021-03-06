#pragma once

#include "solution.h"


// Библиотека содержит функции для решения кубических уравнений вида
//                    X^3 + aX^2 + bX + c = 0
// Расчеты проводятся по аналитическим формулам Кардано.
// Решение сохраняется в типе NCubicEq::TSolution

namespace NMySpace::NPhan::NCubicEq {
    
    using Solver = TSolution(double a, double b, double c);

}
