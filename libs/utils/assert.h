#include "make_string.h"

#define ASSERT_EX(CONDITION, EXCEPTION, MESSAGE) { \
    if (!(CONDITION)) { \
        throw EXCEPTION(MySpace::Utility::MakeString() << "Got '" << std::string(MESSAGE) \
                                                       << "' by failing the condition '" \
                                                       << #CONDITION << "' in function '" \
                                                       << __func__ << "' in line " << __LINE__ \
                                                       << " from file " << __FILE__); \
    } \
}
