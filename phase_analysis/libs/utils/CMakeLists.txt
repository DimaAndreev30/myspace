add_library(
    phan_utils 
    math.cpp
    easy_sort.cpp
    #sparse.cpp
)
target_link_libraries(phan_utils utils)

## Тесты:
add_subdirectory(ut)
