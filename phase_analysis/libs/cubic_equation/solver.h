#pragma once


// Библиотеки содержат функции для решения кубических уравнений вида
//                    X^3 + aX^2 + bX + c = 0
// Расчеты проводятся по аналитическим формулам Кардано.
// Решение сохраняется в типе NCubicEq::TSolution

#include "solution.h"

 
namespace NMySpace::NPhan::NCubicEq {
    
    using Solver = TSolution(double a, double b, double c);

}
