#pragma once

#include "exceptions.h"
#include "make_string.h"


#define MY_ENSURE_EX(CONDITION, EXCEPTION, MESSAGE) { \
    if (!(CONDITION)) { \
        throw EXCEPTION(NMySpace::NUtils::TMakeString() \
            << __FILE__ << ":" << __LINE__ << " in " << __func__ \
            << " ASSERTION FAILED MY_ENSURE_EX(" << #CONDITION \
            << "): " << MESSAGE); \
    } \
}

#define MY_ENSURE(CONDITION, MESSAGE) MY_ENSURE_EX(CONDITION, NMySpace::NUtils::TException, MESSAGE)
