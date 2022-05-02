#pragma once

#include "solver.h"


namespace NMySpace::NPhan::NCubicEq {
        
    // Простейшая прямолинейная реализация:
    // - потери точности в меньших по абсолютному значению корнях
    // - не умеет детектировать кратные корни
    // - не считает мнимые корни
    TSolution SimpleSolve(double a, double b, double c);

}
