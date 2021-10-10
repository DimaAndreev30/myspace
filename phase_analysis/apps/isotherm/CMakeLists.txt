add_subdirectory(src)

add_executable(isotherm main.cpp)
target_link_libraries(
    isotherm 
    isotherm_plot_by_V 
    isotherm_plot_by_P 
    ${cubic_eos}
)