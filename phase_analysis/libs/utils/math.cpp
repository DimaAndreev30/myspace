#include "math.h"

#include <cmath>


namespace MySpace::Utility
{


double sign_save_pow(double x, double y) {
    return x > 0 ? std::exp(y*std::log(x)) : -std::exp(y*std::log(-x));
}

    
} // namespace MySpace::Utility;