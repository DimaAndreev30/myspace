add_library(phan_cubic_eos_constants constants.cpp)

add_library(
    phan_cubic_eos 
    eos.cpp
    params.cpp
)
target_link_libraries(
    phan_cubic_eos 
    phan_cubic_eos_constants
    phan_utils
    phan_cubic_equation
)

add_library(phan_cubic_eos_RK RK.cpp)
target_link_libraries(phan_cubic_eos_RK phan_cubic_eos)

add_library(phan_cubic_eos_SRK SRK.cpp)
target_link_libraries(phan_cubic_eos_SRK phan_cubic_eos)

add_library(phan_cubic_eos_PR PR.cpp)
target_link_libraries(phan_cubic_eos_PR phan_cubic_eos)
