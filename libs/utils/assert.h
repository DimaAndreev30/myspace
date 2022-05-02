#pragma once

#include "exceptions.h"
#include "strings.h"


#define MY_THROW_EX(EXCEPTION, MESSAGE) { \
    throw EXCEPTION(NMySpace::NUtils::TStringBuilder() \
        << __FILE__ << ":" << __LINE__ << " in " << __func__ << ": " << MESSAGE); \
}

#define MY_THROW(MESSAGE) MY_THROW_EX(NMySpace::NUtils::TException, MESSAGE)

#define MY_ENSURE_EX(CONDITION, EXCEPTION, MESSAGE) { \
    if (!(CONDITION)) MY_THROW_EX( \
        EXCEPTION, \
        "ASSERTION FAILED ON (" << #CONDITION << "): " << MESSAGE \
    ) \
}

#define MY_ENSURE(CONDITION, MESSAGE) MY_ENSURE_EX(CONDITION, NMySpace::NUtils::TEnsureFailedException, MESSAGE)
