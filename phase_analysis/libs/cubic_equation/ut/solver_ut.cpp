#include <gtest/gtest.h>

#include <phase_analysis/libs/cubic_equation/solver.h>
#include <phase_analysis/libs/cubic_equation/simple.h>

#include <phase_analysis/libs/utils/easy_sort.h>

#include <ostream>
#include <stdexcept>
#include <vector>

using namespace NMySpace::NPhan::NCubicEq;
using namespace NMySpace::NPhan::NUtils;


struct TTestCase {
    double a, b, c;
    TSolution s;
    bool EnableTestImaginary = false;
};

std::ostream& operator<<(std::ostream& out, const TTestCase& test) {
    out << test.s
        << "\ncoefficients:\n"
        << std::setw(12) << test.a << " "
        << std::setw(12) << test.b << " "
        << std::setw(12) << test.c << " ";
    
    return out;
}

TTestCase makeThreeRootCase(
    double x1, double x2, double x3, 
    TSolution::EType type = TSolution::EType::Three
) {
    if (type == TSolution::EType::One) {
        throw std::invalid_argument("Incorrect case type: one root when there are three");
    }
    
    auto res = TTestCase{
        .a = -(x1 + x2 + x3),
        .b = (x1*x2 + x2*x3 + x3*x1),
        .c = -x1*x2*x3,
        .s = TSolution{
            .Type = type,
            .At = {x1, x2, x3},
        },
    };
   
    sortAbs3(res.s.At.data());
    
    return res;
}

TTestCase makeOneRootCase(
    double x1, double x2, double y2, 
    bool enableTestImaginary = false
) {
    double r = x2*x2 + y2*y2;
    
    return TTestCase{
        .a = -(x1 + 2*x2),
        .b = 2*x1*x2 + r,
        .c = -x1*r,
        .s = TSolution{
            .Type = TSolution::EType::One,
            .At = {x1, x2, y2},
        },
        .EnableTestImaginary = enableTestImaginary,
    };
}

void testCase(const TTestCase& test, Solver solver) {
    TSolution s = solver(test.a, test.b, test.c);
    ASSERT_EQ(test.s.Type, s.Type);
    
    if (test.s.Type == TSolution::EType::One) {
        EXPECT_NEAR(test.s.Im.Real, s.Im.Real, 1e-5) << "Real root failed on case:\n" << test;
            
        if (test.EnableTestImaginary) {
            EXPECT_NEAR(test.s.Im.Complex.Re, s.Im.Complex.Re, 1e-5) << "Real part failed on case:\n" << test;
            EXPECT_NEAR(test.s.Im.Complex.Im, s.Im.Complex.Im, 1e-5) << "Imaginary part failed on case:\n" << test;
        }
    } else {
        sortAbs3(s.At.data());
        
        EXPECT_NEAR(test.s.At[0], s.At[0], 1e-5) << "Smallest root failed on case:\n" << test;
        EXPECT_NEAR(test.s.At[1], s.At[1], 1e-5) << "Middle root failed on case:\n" << test;
        EXPECT_NEAR(test.s.At[2], s.At[2], 1e-5) << "Largest root failed on case:\n" << test;
    }
}


using TSuitcase = std::vector<TTestCase>;

void testSuitcase(const TSuitcase& suitcase, Solver solver) {
    for (const auto& test : suitcase) {
        testCase(test, solver);
    }
}

const TSuitcase basicOneRoot = {
    makeOneRootCase(1, 1, 1),
    makeOneRootCase(1, -1, 1),
    makeOneRootCase(-1, 1, 1),
    makeOneRootCase(-1, -1, 1)
};
    
const TSuitcase AdvancedOneRoot = {
    makeOneRootCase(12.21542534, 5321.215432, 315.2354532),
    makeOneRootCase(43.1324432, -0.144532, 33.12345324),
    makeOneRootCase(-6431.432646, 4325.876542, 994.684)
};

const TSuitcase basicThreeRoot = {
    makeThreeRootCase(1, 2, 3),
    makeThreeRootCase(-1, -2, -3),
    makeThreeRootCase(1, 2, -3),
    makeThreeRootCase(-1, -2, 3),
    makeThreeRootCase(1, -2, 3)
};
    
const TSuitcase AdvancedThreeRoot = {
    makeThreeRootCase(12.21542534, 315.2354532, 5321.215432),
    makeThreeRootCase(-0.144532, 33.12345324, 43.1324432),
    makeThreeRootCase(994.684, 4325.876542, -6431.432646)
};
    
TEST(PhanCubicEquationTest, basic) {
    testSuitcase(basicOneRoot, simpleSolve);
    testSuitcase(AdvancedOneRoot, simpleSolve);
    testSuitcase(basicThreeRoot, simpleSolve);
    testSuitcase(AdvancedThreeRoot, simpleSolve);
}
