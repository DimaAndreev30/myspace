add_library(
    phan_cubic_equation
    formulas.cpp
    simple.cpp 
    solution.cpp
)

## Тесты:
add_subdirectory(ut)
