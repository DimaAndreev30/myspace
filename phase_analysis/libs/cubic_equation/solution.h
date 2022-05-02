#pragma once

#include <array>
#include <ostream>

 
namespace NMySpace::NPhan::NCubicEq {
    
    /**
    * Тип возвращаемого значения:
    * One,    если имеется ровно один действительный корень
    * Double, если имеется двойной кратный корень
    * Triple, если имеется тройной кратный корень
    * Three,  если имеется три различных действительных корня
    *
    * При расчете мнимых корней, их действительная и мнимая часть записывается
    * на вторую и третью позицию массива At соответственно.
    */
    
    struct TSolution {
        enum class EType {
            One,
            Double,
            Triple,
            Three
        } Type;
        
        union {
            std::array<double, 3> At;
            struct {
                double First, Second, Third;
            } Re;
            struct {
                double Real;
                struct { 
                    double Re, Im; 
                } Complex;
            } Im;
        };
    };

}

std::ostream& operator<<(std::ostream& out, const NMySpace::NPhan::NCubicEq::TSolution& s);
