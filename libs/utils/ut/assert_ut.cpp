#include <gtest/gtest.h>

#include <libs/utils/assert.h>

#include <cstring>
#include <stdexcept>

using namespace MySpace::Utility;


TEST(AssertTest, AssertEx) {
    ASSERT_THROW(MS_ASSERT_EX(false, std::logic_error, "exception"), std::logic_error);
    ASSERT_NO_THROW(MS_ASSERT_EX(true, std::logic_error, "exception"));
    ASSERT_NO_THROW(
        try {
            MS_ASSERT_EX(false, std::logic_error, "exception");
        } catch(const std::logic_error& ex) {
            ASSERT_NE(nullptr, std::strstr(ex.what(), "exception"));
        }
    );
}
