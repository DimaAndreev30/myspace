#include "strings.h"

using namespace NMySpace::NUtils;


std::ostream& operator<< (std::ostream& out, TStringBuilder&& builder) {
    return out << std::move(builder).AsString();
}
