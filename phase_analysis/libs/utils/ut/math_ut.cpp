#include <gtest/gtest.h>

#include <phase_analysis/libs/utils/math.h>

using namespace NMySpace::NPhan::NUtils;
    

static const double REL_ERROR = 1e-12;

TEST(PhanUtilsMathTest, singSavePow) {
    ASSERT_NEAR(+4.0, signSavePow(+2.0, 2.0), REL_ERROR);
    ASSERT_NEAR(-4.0, signSavePow(-2.0, 2.0), REL_ERROR);
    
    ASSERT_NEAR(+signSavePow(+1.00123451, 2.2), 
                -signSavePow(-1.00123451, 2.2), 
                REL_ERROR);
}
