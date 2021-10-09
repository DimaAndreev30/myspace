add_library(math math.cpp)
add_library(easy_sort easy_sort.cpp)

add_library(utils math easy_sort)

## Тесты:
add_subdirectory(ut)