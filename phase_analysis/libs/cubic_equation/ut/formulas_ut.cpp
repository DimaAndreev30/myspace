#include <gtest/gtest.h>

#include <phase_analysis/libs/cubic_equation/formulas.h>

using namespace NMySpace::NPhan::NCubicEq;


TEST(PhanCubicEquationTest, getAlphaPlusBeta) {
    EXPECT_DOUBLE_EQ(-5.0, getAlphaPlusBeta(6, 17.5, 216, 306.25));
}
