#include <gtest/gtest.h>

#include <vector>

#include <phase_analysis/libs/utils/easy_sort.h>

using namespace NMySpace::NPhan::NUtils;
    
    
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

class TSortCase {
public:
    enum ECaseType {
        Ascending,
        Descending,
        AbsAscending,
        AbsDescending
    };
    
public:
    TSortCase(ECaseType type)
    {
        setCase(type);
    }
    
    void testOn(double array[3]) const {
        double arrayCopy[3] = {array[0], array[1], array[2]};
        
        Sort_(arrayCopy);
        ASSERT_TRUE(Check_(arrayCopy)) 
            << Case_ << " case failed: for {" 
            << array[0] << "," << array[1] << "," << array[2] << "}, got {"
            << arrayCopy[0] << "," << arrayCopy[1] << "," << arrayCopy[2] << "}";
    }
    
    void setCase(ECaseType type) {
        switch (type) {
            case Ascending:
                Case_ = "ascending sort";
                Sort_ = sort3;
                Check_ = checkSorted;
                break;
            case Descending:
                Case_ = "descending sort";
                Sort_ = sort3Desc;
                Check_ = checkSortedDesc;
                break;
            case AbsAscending:
                Case_ = "abs ascending sort";
                Sort_ = sortAbs3;
                Check_ = checkSortedAbs;
                break;
            case AbsDescending:
                Case_ = "abs descending sort";
                Sort_ = sortAbs3Desc;
                Check_ = checkSortedAbsDesc;
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
    
    
class PhanUtilsEasySortTest : public ::testing::Test {
protected:
    PhanUtilsEasySortTest()
    {
        Cases_.emplace_back(TSortCase::ECaseType::Ascending);
        Cases_.emplace_back(TSortCase::ECaseType::Descending);
        Cases_.emplace_back(TSortCase::ECaseType::AbsAscending);
        Cases_.emplace_back(TSortCase::ECaseType::AbsDescending);
    }
    
    void testOn(double a, double b, double c) const {
        for (const auto& sortCase : Cases_) {
            double array[3] = {a, b, c};
            sortCase.testOn(array);
        }
    }

    std::vector<TSortCase> Cases_;
};
    
TEST_F(PhanUtilsEasySortTest, BasicTests) {
    testOn(1, 2, 3);
    testOn(2, 3, 1);
    testOn(3, 1, 2);
    testOn(1, 3, 2);
    testOn(3, 2, 1);
    testOn(2, 1, 3);
}

TEST_F(PhanUtilsEasySortTest, BorderTests) {
    testOn(1, 1, 1);
    testOn(1, 1, 2);
    testOn(1, 2, 1);
    testOn(2, 1, 1);
}
