#pragma once


namespace MySpace::PhAn::CubicEquation {

    // Функция, *точно* расчитывающая сумму alpha + beta из формулы для 
    // единственного действительного корня с использованием формул Тейлора.
    double getAlphaPlusBeta(double p, double q, double p3, double q2);
    
} // namespace MySpace::PhAn::CubicEquation;

