set(SOURCE_FILES
    math_ut.cpp
    easy_sort_ut.cpp
)

add_executable(runPhanUtilsTest ${SOURCE_FILES})
target_link_libraries(runPhanUtilsTest ${phan_utils} gtest gtest_main)

add_test(NAME runPhanUtilsTest COMMAND runPhanUtilsTest)