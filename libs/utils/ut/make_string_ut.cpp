#include <gmock/gmock.h>

#include <libs/utils/make_string.h>

using namespace NMySpace::NUtils;


TEST(UtilsMakeStringTest, common) {
    ASSERT_EQ("", (TMakeString()).asString());
    ASSERT_EQ("qwerty", (TMakeString() << "qwerty").asString());
    ASSERT_EQ("qwerty", (TMakeString() << "qwe" << "rty").asString());
    ASSERT_EQ("qwerty", (TMakeString() << 'q' << 'w' << 'e' << 'r' << 't' << 'y').asString());
    
    std::string str = TMakeString() << "qwerty";
    ASSERT_EQ("qwerty", str);
}
