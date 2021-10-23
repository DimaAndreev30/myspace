set(SOURCE_FILES
    make_string_ut.cpp
    assert_ut.cpp
)

add_executable(run_utils_test ${SOURCE_FILES})
target_link_libraries(run_utils_test ${phan_utils} gtest gtest_main)

add_test(NAME run_utils_test COMMAND run_utils_test)
