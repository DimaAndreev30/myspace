add_library(utils_math math.cpp)
add_library(utils_easy_sort easy_sort.cpp)

set(phan_utils utils_math utils_easy_sort)

## Тесты:
add_subdirectory(ut)