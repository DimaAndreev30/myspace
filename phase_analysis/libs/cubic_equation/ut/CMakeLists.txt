set(SOURCE_FILES
    solver_ut.cpp
)

add_executable(runCubicEquationTest ${SOURCE_FILES})
target_link_libraries(
    runCubicEquationTest 
    ${cubic_eq_solvers} easy_sort gtest gtest_main
    )

add_test(NAME runCubicEquationTest COMMAND runCubicEquationTest)