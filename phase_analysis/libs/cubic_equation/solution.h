#pragma once

#include <array>

 
namespace MySpace::PhAn::CubicEquation {
    
    /**
    * Решение сохраняется в массиве roots из трех элементов.
    * Тип возвращаемого значения:
    * ONE_ROOT,    если имеется ровно один действительный корень
    * TRIPLE_ROOT, если имеется тройной кратный корень
    * DOUBLE_ROOT, если имеется двойной кратный корень
    * THREE_ROOT,  если имеется три различных действительных корня
    *
    * При расчете мнимых корней, их действительная и мнимая часть записывается
    * на вторую и третью позицию массива roots соответственно.
    */
    
    struct Solution {
        enum Type {
            ONE_ROOT,
            TRIPLE_ROOT,
            DOUBLE_ROOT,
            THREE_ROOT
        } type;
        
        std::array<double, 3> roots;
    };

} // namespace MySpace::PhAn::CubicEquation;