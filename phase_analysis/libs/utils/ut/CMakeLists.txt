set(SOURCE_FILES
    math_ut.cpp
    easy_sort_ut.cpp
)

add_executable(run_phan_utils_test ${SOURCE_FILES})
target_link_libraries(run_phan_utils_test ${phan_utils} gtest gtest_main)

add_test(NAME run_phan_utils_test COMMAND run_phan_utils_test)
