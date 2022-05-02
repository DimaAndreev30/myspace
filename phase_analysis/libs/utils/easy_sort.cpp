#include "easy_sort.h"

#include <algorithm>
#include <cmath>


namespace NMySpace::NPhan::NUtils {

    void Sort3(double array[3]) {
        if (array[0] > array[1]) {
            std::swap(array[0], array[1]);
        }
        if (array[1] > array[2]) {
            std::swap(array[1], array[2]);
            if (array[0] > array[1]) {
                std::swap(array[0], array[1]);
            }
        }
    }

    void Sort3Desc(double array[3]) {
        if (array[0] < array[1]) {
            std::swap(array[0], array[1]);
        }
        if (array[1] < array[2]) {
            std::swap(array[1], array[2]);
            if (array[0] < array[1]) {
                std::swap(array[0], array[1]);
            }
        }
    }


    void SortAbs3(double array[3]) {
        if (std::abs(array[0]) > std::abs(array[1])) {
            std::swap(array[0], array[1]);
        }
        if (std::abs(array[1]) > std::abs(array[2])) {
            std::swap(array[1], array[2]);
            if (std::abs(array[0]) > std::abs(array[1])) {
                std::swap(array[0], array[1]);
            }
        }
    }

    void SortAbs3Desc(double array[3]) {
        if (std::abs(array[0]) < std::abs(array[1])) {
            std::swap(array[0], array[1]);
        }
        if (std::abs(array[1]) < std::abs(array[2])) {
            std::swap(array[1], array[2]);
            if (std::abs(array[0]) < std::abs(array[1])) {
                std::swap(array[0], array[1]);
            }
        }
    }
 
}
