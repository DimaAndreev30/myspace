#pragma once


// Библиотеки содержат функции для решения кубических уравнений вида
//                    X^3 + aX^2 + bX + c = 0
// Расчеты проводятся по аналитическим формулам Кардано.
// Решение сохраняется в типе CubicEquation::Solution

#include "solution.h"

 
namespace MySpace::PhAn::CubicEquation {
    
    using Solver = Solution(double a, double b, double c);

} // namespace MySpace::PhAn::CubicEquation;