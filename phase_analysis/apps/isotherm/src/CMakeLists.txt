set(SOURCES
    cubic_eos_interface
)

add_library(isotherm_plot_by_V plot_by_V.cpp)
target_link_libraries(isotherm_plot_by_V ${SOURCES})

add_library(isotherm_plot_by_P plot_by_P.cpp)
target_link_libraries(isotherm_plot_by_P ${SOURCES})
