#include <gtest/gtest.h>

#include <libs/utils/make_string.h>

using namespace MySpace::Utility;


TEST(UtilsMakeStringTest, Test) {
    ASSERT_EQ("", (MakeString()).asString());
    ASSERT_EQ("qwerty", (MakeString() << "qwerty").asString());
    ASSERT_EQ("qwerty", (MakeString() << "qwe" << "rty").asString());
    ASSERT_EQ("qwerty", (MakeString() << 'q' << 'w' << 'e' << 'r' << 't' << 'y').asString());
    
    std::string str = MakeString() << "qwerty";
    ASSERT_TRUE("qwerty" == str);
}
