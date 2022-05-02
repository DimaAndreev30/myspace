#include <gtest/gtest.h>

#include <phase_analysis/libs/utils/easy_sort.h>

#include <vector>

using namespace NMySpace::NPhan::NUtils;
    
    
static bool CheckSorted(double array[3]) {
    return array[0] <= array[1] && array[1] <= array[2];
}

static bool CheckSortedDesc(double array[3]) {
    return array[0] >= array[1] && array[1] >= array[2];
}

static bool CheckSortedAbs(double array[3]) {
    return std::abs(array[0]) <= std::abs(array[1]) && std::abs(array[1]) <= std::abs(array[2]);
}

static bool CheckSortedAbsDesc(double array[3]) {
    return std::abs(array[0]) >= std::abs(array[1]) && std::abs(array[1]) >= std::abs(array[2]);
}

class TSortCase {
public:
    enum ECaseType {
        Ascending,
        Descending,
        AbsAscending,
        AbsDescending
    };
    
public:
    TSortCase(ECaseType type) {
        SetCase(type);
    }
    
    void TestOn(double array[3]) const {
        double arrayCopy[3] = {array[0], array[1], array[2]};
        
        Sort_(arrayCopy);
        ASSERT_TRUE(Check_(arrayCopy)) 
            << Case_ << " case failed: for {" 
            << array[0] << "," << array[1] << "," << array[2] << "}, got {"
            << arrayCopy[0] << "," << arrayCopy[1] << "," << arrayCopy[2] << "}";
    }
    
    void SetCase(ECaseType type) {
        switch (type) {
            case Ascending:
                Case_ = "ascending sort";
                Sort_ = Sort3;
                Check_ = CheckSorted;
                break;
            case Descending:
                Case_ = "descending sort";
                Sort_ = Sort3Desc;
                Check_ = CheckSortedDesc;
                break;
            case AbsAscending:
                Case_ = "abs ascending sort";
                Sort_ = SortAbs3;
                Check_ = CheckSortedAbs;
                break;
            case AbsDescending:
                Case_ = "abs descending sort";
                Sort_ = SortAbs3Desc;
                Check_ = CheckSortedAbsDesc;
                break;
        }
    }  
    
private:
    const char* Case_;

    using SortFunc = void(double[3]);
    SortFunc* Sort_;
    
    using CheckFunc = bool(double[3]);
    CheckFunc* Check_;
};
    
    
class PhanUtilsEasySortTest: public ::testing::Test {
protected:
    PhanUtilsEasySortTest()
    {
        Cases_.emplace_back(TSortCase::ECaseType::Ascending);
        Cases_.emplace_back(TSortCase::ECaseType::Descending);
        Cases_.emplace_back(TSortCase::ECaseType::AbsAscending);
        Cases_.emplace_back(TSortCase::ECaseType::AbsDescending);
    }
    
    void TestOn(double a, double b, double c) const {
        for (const auto& sortCase : Cases_) {
            double array[3] = {a, b, c};
            sortCase.TestOn(array);
        }
    }

private:
    std::vector<TSortCase> Cases_;
};
    
TEST_F(PhanUtilsEasySortTest, BasicTests) {
    TestOn(1, 2, 3);
    TestOn(2, 3, 1);
    TestOn(3, 1, 2);
    TestOn(1, 3, 2);
    TestOn(3, 2, 1);
    TestOn(2, 1, 3);
}

TEST_F(PhanUtilsEasySortTest, BorderTests) {
    TestOn(1, 1, 1);
    TestOn(1, 1, 2);
    TestOn(1, 2, 1);
    TestOn(2, 1, 1);
}
