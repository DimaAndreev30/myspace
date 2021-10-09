#pragma once

#include <array>

namespace MySpace::PhAn::CubicEquation {
    
    struct Solution {
        enum Type {
            ONE_ROOT,
            TRIPLE_ROOT,
            DOUBLE_ROOT,
            THREE_ROOT
        } type;
        
        std::array<double, 3> roots;
    };
    
    using Solver = Solution(double a, double b, double c);

} // namespace MySpace::PhAn::CubicEquation;