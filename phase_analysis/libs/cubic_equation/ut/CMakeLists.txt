set(SOURCE_FILES
    solver_ut.cpp
)

add_executable(runCubicEquationTest ${SOURCE_FILES})
target_link_libraries(
    runCubicEquationTest 
    ${cubic_equation_solver} phan_utils_easy_sort gtest gtest_main
)

add_test(NAME runCubicEquationTest COMMAND runCubicEquationTest)