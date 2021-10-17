add_library(cubic_eos_constants constants.cpp)

add_library(cubic_eos_interface interface.cpp)
target_link_libraries(
    cubic_eos_interface 
    cubic_eos_constants
    phan_utils_easy_sort
    cubic_equation_simple
)

add_library(cubic_eos_RK RK.cpp)
target_link_libraries(cubic_eos_RK cubic_eos_interface)

add_library(cubic_eos_SRK SRK.cpp)
target_link_libraries(cubic_eos_SRK cubic_eos_interface)

add_library(cubic_eos_PR PR.cpp)
target_link_libraries(cubic_eos_PR cubic_eos_interface)

set(cubic_eos cubic_eos_RK cubic_eos_SRK cubic_eos_PR CACHE INTERNAL "" FORCE)

add_subdirectory(mixture)