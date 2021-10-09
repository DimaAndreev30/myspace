add_library(math_util math.cpp)
add_library(easy_sort easy_sort.cpp)

set(phan_utils math_util easy_sort)

## Тесты:
add_subdirectory(ut)