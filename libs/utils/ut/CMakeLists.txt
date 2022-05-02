add_executable(
    run_utils_test 
    assert_ut.cpp
    exceptions_ut.cpp
    strings_ut.cpp
)
target_link_libraries(run_utils_test utils gmock gmock_main)

add_test(NAME run_utils_test COMMAND run_utils_test)
