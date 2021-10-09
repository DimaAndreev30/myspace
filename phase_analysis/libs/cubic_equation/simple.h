#pragma once

#include "solution.h"


namespace MySpace::PhAn::CubicEquation {
        
    // Простейшая прямолинейная реализация:
    // - потери точности в меньших по абсолютному значению корнях
    // - не умеет детектировать кратные корни
    // - не считает мнимые корни
    Solution solve(double a, double b, double c);

} // namespace MySpace::PhAn::CubicEquation;