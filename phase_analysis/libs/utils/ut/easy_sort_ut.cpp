#include <gtest/gtest.h>

#include <vector>

#include <phase_analysis/libs/utils/easy_sort.h>

using namespace MySpace::Utility;
    
    
bool checkSorted(double array[3]) {
    return array[0] <= array[1] && array[1] <= array[2];
}

bool checkSortedDesc(double array[3]) {
    return array[0] >= array[1] && array[1] >= array[2];
}

bool checkSortedAbs(double array[3]) {
    return std::abs(array[0]) <= std::abs(array[1]) && std::abs(array[1]) <= std::abs(array[2]);
}

bool checkSortedAbsDesc(double array[3]) {
    return std::abs(array[0]) >= std::abs(array[1]) && std::abs(array[1]) >= std::abs(array[2]);
}

class SortCase {
public:
    enum CaseType {
        ASCENDING,
        DESCENDING,
        ABS_ASCENDING,
        ABS_DESCENDING
    };
    
public:
    SortCase(CaseType type)
    {
        setCase(type);
    }
    
    void testOn(double array[3]) const {
        sort(array);
        ASSERT_TRUE(check(array)) << "failed in " << case_ << "case";
    }
    
    void setCase(CaseType type) {
        switch (type) {
            case ASCENDING:
                case_ = "ascending sort";
                sort = sort3;
                check = checkSorted;
                break;
            case DESCENDING:
                case_ = "descending sort";
                sort = sort3Desc;
                check = checkSortedDesc;
                break;
            case ABS_ASCENDING:
                case_ = "abs ascending sort";
                sort = sortAbs3;
                check = checkSortedAbs;
                break;
            case ABS_DESCENDING:
                case_ = "abs descending sort";
                sort = sortAbs3Desc;
                check = checkSortedAbsDesc;
                break;
        }
    }  
    
private:
    const char* case_;

    using SortFunc = void(double[3]);
    SortFunc* sort;
    
    using CheckFunc = bool(double[3]);
    CheckFunc* check;
};
    
    
class EasySortTest : public ::testing::Test {
protected:
    EasySortTest()
    {
        cases_.emplace_back(SortCase::ASCENDING);
        cases_.emplace_back(SortCase::DESCENDING);
        cases_.emplace_back(SortCase::ABS_ASCENDING);
        cases_.emplace_back(SortCase::ABS_DESCENDING);
    }
    
    void testOn(double a, double b, double c) const {
        for (const auto& sortCase : cases_) {
            double array[] = {a, b, c};
            sortCase.testOn(array);
        }
    }

    std::vector<SortCase> cases_;
};
    
TEST_F(EasySortTest, BasicTests) {
    testOn(1, 2, 3);
    testOn(2, 3, 1);
    testOn(3, 1, 2);
    testOn(1, 3, 2);
    testOn(3, 2, 1);
    testOn(2, 1, 3);
}

TEST_F(EasySortTest, BorderTests) {
    testOn(1, 1, 1);
    testOn(1, 1, 2);
    testOn(1, 2, 1);
    testOn(2, 1, 1);
}