#include <gtest/gtest.h>

#include <phase_analysis/libs/cubic_equation/solver.h>

#include <phase_analysis/libs/utils/easy_sort.h>

#include <vector>
#include <ostream>
#include <stdexcept>

using namespace MySpace::PhAn::CubicEquation;
using namespace MySpace::PhAn::Utility;

struct cubicEquationTestCase {
    double a, b, c;
    Solution solution;
    bool enableTestImaginary = false;
};

std::ostream& operator<<(std::ostream& out, const cubicEquationTestCase& test) {
    if (test.solution.type == Solution::ONE_ROOT) {
        out << "one real root:\n" << std::setw(12) << test.solution.roots[0] << "\n" 
            << std::setw(12) << test.solution.roots[1] << " +- i*" 
            << std::setw(12) << test.solution.roots[2];
    } else {
        out << "three real roots:\n"
            << std::setw(12) << test.solution.roots[0] << " "
            << std::setw(12) << test.solution.roots[1] << " "
            << std::setw(12) << test.solution.roots[2] << " ";
            
        if (test.solution.type == Solution::TRIPLE_ROOT) {
            out << "\n(triple root)";
        }
        if (test.solution.type == Solution::DOUBLE_ROOT) {
            out << "\n(double root)";
        }
    }
    
    out << "\ncoefficients:\n"
        << std::setw(12) << test.a << " "
        << std::setw(12) << test.b << " "
        << std::setw(12) << test.c << " ";
    
    return out;
}

cubicEquationTestCase makeThreeRootCase(double x1, 
                                        double x2, 
                                        double x3, 
                                        Solution::Type type = Solution::THREE_ROOT) {
    if (type == Solution::ONE_ROOT) {
        throw std::invalid_argument("Incorrect case type: one root when there are three");
    }
    
    auto res = cubicEquationTestCase{
        .a = -(x1 + x2 + x3),
        .b = (x1*x2 + x2*x3 + x3*x1),
        .c = -x1*x2*x3,
        .solution = Solution{
            .type = type,
            .roots = {x1, x2, x3}
        }
    };
    
    sortAbs3(res.solution.roots.data());
    
    return res;
}

cubicEquationTestCase makeOneRootCase(double x1, 
                                      double x2, 
                                      double y2, 
                                      bool enableTestImaginary = false) {
    double r = x2*x2 + y2*y2;
    
    return cubicEquationTestCase{
        .a = -(x1 + 2*x2),
        .b = 2*x1*x2 + r,
        .c = -x1*r,
        .solution = Solution{
            .type = Solution::ONE_ROOT,
            .roots = {x1, x2, y2}
        },
        .enableTestImaginary = enableTestImaginary
    };
}

void testCase(const cubicEquationTestCase& test, Solver solver) {
    Solution solution = solver(test.a, test.b, test.c);
    ASSERT_EQ(test.solution.type, solution.type);
    
    if (test.solution.type == Solution::ONE_ROOT) {
        EXPECT_NEAR(test.solution.roots[0], solution.roots[0], 1e-5) << "Real root failed on case:\n" << test;
            
        if (test.enableTestImaginary) {
            EXPECT_NEAR(test.solution.roots[1], solution.roots[1], 1e-5) << "Real part failed on case:\n" << test;
            EXPECT_NEAR(test.solution.roots[2], solution.roots[2], 1e-5) << "Imaginary part failed on case:\n" << test;
        }
    } else {
        sortAbs3(solution.roots.data());
        
        EXPECT_NEAR(test.solution.roots[0], solution.roots[0], 1e-5) << "Smallest root failed on case:\n" << test;
        EXPECT_NEAR(test.solution.roots[1], solution.roots[1], 1e-5) << "Middle root failed on case:\n" << test;
        EXPECT_NEAR(test.solution.roots[2], solution.roots[2], 1e-5) << "Largest root failed on case:\n" << test;
    }
}


using Suitcase = std::vector<cubicEquationTestCase>;

const Suitcase basicOneRoot = {
    makeOneRootCase(1, 1, 1),
    makeOneRootCase(1, -1, 1),
    makeOneRootCase(-1, 1, 1),
    makeOneRootCase(-1, -1, 1)
};
    
const Suitcase AdvancedOneRoot = {
    makeOneRootCase(12.21542534, 5321.215432, 315.2354532),
    makeOneRootCase(43.1324432, -0.144532, 33.12345324),
    makeOneRootCase(-6431.432646, 4325.876542, 994.684)
};

const Suitcase basicThreeRoot = {
    makeThreeRootCase(1, 2, 3),
    makeThreeRootCase(-1, -2, -3),
    makeThreeRootCase(1, 2, -3),
    makeThreeRootCase(-1, -2, 3),
    makeThreeRootCase(1, -2, 3)
};
    
const Suitcase AdvancedThreeRoot = {
    makeThreeRootCase(12.21542534, 315.2354532, 5321.215432),
    makeThreeRootCase(-0.144532, 33.12345324, 43.1324432),
    makeThreeRootCase(994.684, 4325.876542, -6431.432646)
};


void testSuitcase(const Suitcase& suitcase, Solver solver) {
    for (const auto& test : suitcase) {
        testCase(test, solver);
    }
}
    
TEST(SimpleSolverTest, BasicSuitCase) {
    testSuitcase(basicOneRoot, solve);
    testSuitcase(AdvancedOneRoot, solve);
    testSuitcase(basicThreeRoot, solve);
    testSuitcase(AdvancedThreeRoot, solve);
}