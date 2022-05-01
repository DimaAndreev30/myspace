add_executable(
    run_phan_cubic_equation_test 
    formulas_ut.cpp
    solution_ut.cpp
    solver_ut.cpp
)
target_link_libraries(
    run_phan_cubic_equation_test 
    phan_cubic_equation 
    phan_utils 
    gtest 
    gtest_main
)

add_test(NAME run_phan_cubic_equation_test COMMAND run_phan_cubic_equation_test)
