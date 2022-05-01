add_executable(FD main.cpp)
target_link_libraries(
    FD
    FD_by_P
    FD_along_c
    ${cubic_eos}
)
