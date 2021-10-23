set(SOURCE_FILES
    make_string_ut.cpp
    assert_ut.cpp
)

add_executable(runUtilsTest ${SOURCE_FILES})
target_link_libraries(runUtilsTest ${phan_utils} gtest gtest_main)

add_test(NAME runUtilsTest COMMAND runUtilsTest)