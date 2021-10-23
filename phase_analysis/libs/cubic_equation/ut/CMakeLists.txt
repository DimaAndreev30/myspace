set(SOURCE_FILES
    solver_ut.cpp
)

add_executable(run_cubic_equation_test ${SOURCE_FILES})
target_link_libraries(
    run_cubic_equation_test 
    cubic_equation_simple 
    phan_utils_easy_sort 
    gtest 
    gtest_main
)

add_test(NAME run_cubic_equation_test COMMAND run_cubic_equation_test)
