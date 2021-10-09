add_library(cubic_equation_simple simple.cpp formulas.cpp)

set(cubic_equation_solver cubic_equation_simple)

## Тесты:
add_subdirectory(ut)