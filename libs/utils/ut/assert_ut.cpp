#include <gmock/gmock.h>

#include <libs/utils/assert.h>

using namespace NMySpace::NUtils;


#define CHECK(CODE, EXPECTED_EXCEPTION, EXPECTED_MESSAGE) { \
    try { \
        { CODE; } \
    } catch(const EXPECTED_EXCEPTION& e) { \
        ASSERT_THAT(e.what(), ::testing::EndsWith(EXPECTED_MESSAGE)); \
    } \
}

TEST(UtilsAssertTest, common) {
    ASSERT_NO_THROW(MY_ENSURE_EX(true, std::logic_error, "exception"));
    
    CHECK(
        MY_ENSURE_EX(false, std::logic_error, "exception"), 
        std::logic_error,
        "ASSERTION FAILED MY_ENSURE_EX(false): exception"
    )
    CHECK(
        MY_ENSURE_EX(false, std::logic_error, "exception" << " " << "kek"), 
        std::logic_error,
        "ASSERTION FAILED MY_ENSURE_EX(false): exception kek"
    )
    CHECK(
        MY_ENSURE(false, "my exception"), 
        TException,
        "ASSERTION FAILED MY_ENSURE_EX(false): my exception"
    )
}
