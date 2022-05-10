#include <gtest/gtest.h>

#include <phase_analysis/libs/utils/sparse.h>
#include <libs/utils/assert.h>

#include <array>

using namespace NMySpace::NPhan::NUtils;
    

TEST(PhanUtilsSparseTest, Builder) {
}

TEST(PhanUtilsSparseTest, Row) {
    TSparseRow<double> row(10);
    
    ASSERT_DOUBLE_EQ(row[0], 0.0);
    ASSERT_DOUBLE_EQ(row[7], 0.0);
    ASSERT_THROW(row[10], NMySpace::NUtils::TOutOfRangeException);
    
    row[3] = 1.1;
    ASSERT_DOUBLE_EQ(row[3], 1.1);
    
    row[7] = 2.2;
    row[5] = 3.3;
    
    int count = 0;
    std::array<int, 3> expectedIndexes = {3, 5, 7};
    std::array<double, 3> expectedValues = {1.1, 3.3, 2.2};
    for (const auto& val: row) {
        ASSERT_LT(count, 3);
        ASSERT_EQ(val.first, expectedIndexes[count]);
        ASSERT_DOUBLE_EQ(val.second, expectedValues[count]);
        count += 1;
    }
}
