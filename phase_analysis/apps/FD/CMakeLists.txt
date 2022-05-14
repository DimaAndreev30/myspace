add_subdirectory(src)

add_executable(phan_FD main.cpp)
target_link_libraries(
    phan_FD
    phan_FD_mixture_factory
    phan_pheq_flash
    phan_pheq_wilson
    phan_utils
    phan_cubic_eos_RK
    phan_cubic_eos_SRK
    phan_cubic_eos_PR
)
