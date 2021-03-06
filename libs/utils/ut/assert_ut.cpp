#include <gmock/gmock.h>

#include <libs/utils/assert.h>

using namespace NMySpace::NUtils;


#define CHECK(CODE, EXPECTED_EXCEPTION, EXPECTED_MESSAGE) { \
    try { \
        CODE; \
    } catch(const EXPECTED_EXCEPTION& e) { \
        ASSERT_THAT(e.what(), ::testing::EndsWith(EXPECTED_MESSAGE)); \
    } \
}

TEST(UtilsAssertTest, Common) {
    CHECK(
        MS_THROW_EX(std::logic_error, "exception"), 
        std::logic_error,
        "exception"
    )
    CHECK(
        MS_THROW_EX(std::logic_error, "got" << " some " << "exception"), 
        std::logic_error,
        "got some exception"
    )
    CHECK(
        MS_THROW("my exception"), 
        TException,
        "my exception"
    )
    
    ASSERT_NO_THROW(MS_ENSURE(true, "exception"));
    ASSERT_NO_THROW(MS_ENSURE(true && 10 == 10, "exception"));
    ASSERT_NO_THROW(MS_ENSURE(false || true, "exception"));
    ASSERT_NO_THROW(MS_ENSURE(!(10 == 20), "exception"));
    
    CHECK(
        MS_ENSURE_EX(false, std::logic_error, "exception"), 
        std::logic_error,
        "ASSERTION FAILED ON (false): exception"
    )
    CHECK(
        MS_ENSURE_EX(false, std::logic_error, "exception" << " " << "kek"), 
        std::logic_error,
        "ASSERTION FAILED ON (false): exception kek"
    )
    CHECK(
        MS_ENSURE(false, "my exception"), 
        TEnsureFailedException,
        "ASSERTION FAILED ON (false): my exception"
    )
}
