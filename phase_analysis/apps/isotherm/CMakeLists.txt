add_subdirectory(src)

add_executable(phan_isotherm main.cpp)
target_link_libraries(
    phan_isotherm 
    phan_isotherm_plot_by_V 
    phan_isotherm_plot_by_P
    phan_cubic_eos_RK
    phan_cubic_eos_SRK
    phan_cubic_eos_PR
)
