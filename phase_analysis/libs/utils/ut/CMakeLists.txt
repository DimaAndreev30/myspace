set(SOURCE_FILES
    math_ut.cpp
    easy_sort_ut.cpp
)

add_executable(runUtilsTest ${SOURCE_FILES})
target_link_libraries(runUtilsTest utils gtest gtest_main)

add_test(NAME runUtilsTest COMMAND runUtilsTest)