#include "solution.h"

using namespace NMySpace::NPhan::NCubicEq;


std::ostream& operator<<(std::ostream& out, const TSolution& s) {
    if (s.Type == TSolution::EType::One) {
        out << s.Im.Real << ", \t" << s.Im.Complex.Re << " \t+- i*" << s.Im.Complex.Im;
    } else {
        out << s.Re.First << ", \t" << s.Re.Second << ", \t" << s.Re.Third;
    }
    
    return out;
}
