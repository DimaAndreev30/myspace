#pragma once


namespace NMySpace::NPhan::NCubicEq {

    // Функция, *точно* расчитывающая сумму alpha + beta из формулы для 
    // единственного действительного корня с использованием формул Тейлора.
    double GetAlphaPlusBeta(double p, double q, double p3, double q2);
    
}
