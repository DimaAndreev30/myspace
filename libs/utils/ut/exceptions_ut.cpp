#include <gmock/gmock.h>

#include <libs/utils/exceptions.h>

using namespace NMySpace::NUtils;


TEST(UtilsExceptionsTest, Common) {
    ASSERT_THAT(TEnsureFailedException().What(), ::testing::StartsWith("EnsureFailed: "));
    ASSERT_THAT(TBadTestException().What(), ::testing::StartsWith("BadTest: "));
}
