#include <gmock/gmock.h>

#include <libs/utils/strings.h>

using namespace NMySpace::NUtils;


TEST(UtilsStringsTest, StringBuilder) {
    ASSERT_EQ("", (TStringBuilder()).AsString());
    ASSERT_EQ("qwerty", (TStringBuilder() << "qwerty").AsString());
    ASSERT_EQ("qwerty", (TStringBuilder() << "qwe" << "rty").AsString());
    ASSERT_EQ("qwerty", (TStringBuilder() << 'q' << 'w' << 'e' << 'r' << 't' << 'y').AsString());
    
    std::string str = TStringBuilder() << "qwerty";
    ASSERT_EQ("qwerty", str);
    
    TStringBuilder builder;
    builder << "qwe" << "rty";
    ASSERT_EQ("qwerty", std::move(builder).AsString());
    builder << 123456;
    ASSERT_EQ("123456", std::move(builder).AsString());
    ASSERT_EQ("", std::move(builder).AsString());
}

TEST(UtilsStringsTest, CreateString) {
    ASSERT_EQ("qwerty", CreateString("qwerty"));
    ASSERT_EQ("qwerty", CreateString("qwe", "rty"));
    ASSERT_EQ("qwerty123456", CreateString("qwerty", 123456));
}
