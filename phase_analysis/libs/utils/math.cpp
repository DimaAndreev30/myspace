#include "math.h"

#include <cmath>


namespace NMySpace::NPhan::NUtils {

    double SignSavePow(double x, double y) {
        return x > 0 ? std::exp(y*std::log(x)) : -std::exp(y*std::log(-x));
    }

}
