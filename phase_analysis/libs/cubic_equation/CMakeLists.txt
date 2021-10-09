add_library(simple_cubic_eq_solver simple.cpp formulas.cpp)

set(cubic_eq_solvers simple_cubic_eq_solver)

## Тесты:
add_subdirectory(ut)