add_library(phan_utils_math math.cpp)
add_library(phan_utils_easy_sort easy_sort.cpp)

set(phan_utils phan_utils_math phan_utils_easy_sort CACHE INTERNAL "" FORCE)

## Тесты:
add_subdirectory(ut)
