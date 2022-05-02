#include <gtest/gtest.h>

#include <phase_analysis/libs/cubic_equation/solution.h>

#include <libs/utils/strings.h>

using namespace NMySpace::NPhan::NCubicEq;
using namespace NMySpace::NUtils;


TEST(PhanCubicEquationTest, Solution) {
    TSolution s;
    
    s = TSolution{
        .At = {1.1, 2.2, 3.3},
    };
    
    EXPECT_DOUBLE_EQ(1.1, s.At[0]);
    EXPECT_DOUBLE_EQ(2.2, s.At[1]);
    EXPECT_DOUBLE_EQ(3.3, s.At[2]);
    
    EXPECT_DOUBLE_EQ(1.1, s.Re.First);
    EXPECT_DOUBLE_EQ(2.2, s.Re.Second);
    EXPECT_DOUBLE_EQ(3.3, s.Re.Third);
    
    EXPECT_DOUBLE_EQ(1.1, s.Im.Real);
    EXPECT_DOUBLE_EQ(2.2, s.Im.Complex.Re);
    EXPECT_DOUBLE_EQ(3.3, s.Im.Complex.Im);
    
    s = TSolution{
        .Type = TSolution::EType::Three,
        .Re = {
            .First = 1.1,
            .Second = 2.2,
            .Third = 3.3,
        },
    };
    
    EXPECT_DOUBLE_EQ(1.1, s.At[0]);
    EXPECT_DOUBLE_EQ(2.2, s.At[1]);
    EXPECT_DOUBLE_EQ(3.3, s.At[2]);
    
    EXPECT_DOUBLE_EQ(1.1, s.Re.First);
    EXPECT_DOUBLE_EQ(2.2, s.Re.Second);
    EXPECT_DOUBLE_EQ(3.3, s.Re.Third);
    
    EXPECT_DOUBLE_EQ(1.1, s.Im.Real);
    EXPECT_DOUBLE_EQ(2.2, s.Im.Complex.Re);
    EXPECT_DOUBLE_EQ(3.3, s.Im.Complex.Im);
    
    ASSERT_EQ("1.1, \t2.2, \t3.3", (TStringBuilder() << s).AsString());
    
    s = TSolution{
        .Type = TSolution::EType::One,
        .Im = {
            .Real = 1.1,
            .Complex = {
                .Re = 2.2,
                .Im = 3.3,
            },
        },
    };
    
    EXPECT_DOUBLE_EQ(1.1, s.At[0]);
    EXPECT_DOUBLE_EQ(2.2, s.At[1]);
    EXPECT_DOUBLE_EQ(3.3, s.At[2]);
    
    EXPECT_DOUBLE_EQ(1.1, s.Re.First);
    EXPECT_DOUBLE_EQ(2.2, s.Re.Second);
    EXPECT_DOUBLE_EQ(3.3, s.Re.Third);
    
    EXPECT_DOUBLE_EQ(1.1, s.Im.Real);
    EXPECT_DOUBLE_EQ(2.2, s.Im.Complex.Re);
    EXPECT_DOUBLE_EQ(3.3, s.Im.Complex.Im);
    
    ASSERT_EQ("1.1, \t2.2 \t+- i*3.3", (TStringBuilder() << s).AsString());
}
