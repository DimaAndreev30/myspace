add_executable(
    run_utils_test 
    make_string_ut.cpp
    assert_ut.cpp
)
target_link_libraries(run_utils_test gmock gmock_main)

add_test(NAME run_utils_test COMMAND run_utils_test)
