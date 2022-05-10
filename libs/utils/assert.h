#pragma once

#include "exceptions.h"
#include "strings.h"


#define MS_THROW_EX(EXCEPTION, MESSAGE) { \
    throw EXCEPTION(NMySpace::NUtils::TStringBuilder() \
        << __FILE__ << ":" << __LINE__ << " in " << __func__ << ": " << MESSAGE); \
}

#define MS_THROW(MESSAGE) MS_THROW_EX(NMySpace::NUtils::TException, MESSAGE)

#define MS_ENSURE_EX(CONDITION, EXCEPTION, MESSAGE) { \
    if (!(CONDITION)) MS_THROW_EX( \
        EXCEPTION, \
        "ASSERTION FAILED ON (" << #CONDITION << "): " << MESSAGE \
    ) \
}

#define MS_ENSURE(CONDITION, MESSAGE) MS_ENSURE_EX(CONDITION, NMySpace::NUtils::TEnsureFailedException, MESSAGE)
