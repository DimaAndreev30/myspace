#include <gtest/gtest.h>

#include <phase_analysis/libs/utils/math.h>

using namespace MySpace::PhAn::Utility;
    
    
class MathSignsavePowTest : public ::testing::Test {
protected:
    static const double REL_ERROR;
};

const double MathSignsavePowTest::REL_ERROR = 1e-12;

/*
TEST_F(MathSignsavePowTest, AccuracyTest) {
    EXPECT_NEAR(4.0, sign_save_pow(2.0, 2.0), REL_ERROR);
    EXPECT_NEAR(9.0, sign_save_pow(3.0, 2.0), REL_ERROR);
    
    EXPECT_NEAR(22.2559304704058e+000, sign_save_pow(12.345, 1.2354), 10*REL_ERROR);
    
    EXPECT_NEAR(4.54407777353542e-024, 
                sign_save_pow(12.345e-20, 1.2354), 
                1e-24*REL_ERROR);
    EXPECT_NEAR(1.09004833497415e+026, 
                sign_save_pow(12.345e+20, 1.2354), 
                1e+26*REL_ERROR);
                
    EXPECT_NEAR(5.55361267321742e+134, sign_save_pow(12.345, 123.54), 1e134*REL_ERROR);
    EXPECT_NEAR(1.03151241065125e+000, sign_save_pow(12.345, 0.012354), REL_ERROR);


    EXPECT_NEAR(4.49318441810251e-002, sign_save_pow(12.345, -1.2345), REL_ERROR);
    
    EXPECT_NEAR(2.2006665595029387e+023, 
                sign_save_pow(12.345e-20, -1.2354), 
                1e23*REL_ERROR);
    EXPECT_NEAR(9.1739051188377704e-027, 
                sign_save_pow(12.345e+20, -1.2354), 
                1e-27*REL_ERROR);
                
    EXPECT_NEAR(1.80062971410045e-135, sign_save_pow(12.345, -123.54), 1e-135*REL_ERROR);
    EXPECT_NEAR(9.69450284527986e-001, sign_save_pow(12.345, -0.012354), REL_ERROR);
}
*/
TEST_F(MathSignsavePowTest, SingTest) {
    
    ASSERT_NEAR(+4.0, sign_save_pow(+2.0, 2.0), REL_ERROR);
    ASSERT_NEAR(-4.0, sign_save_pow(-2.0, 2.0), REL_ERROR);
    
    ASSERT_NEAR(+sign_save_pow(+1.00123451, 2.2), 
                -sign_save_pow(-1.00123451, 2.2), 
                REL_ERROR);
}