add_executable(FD main.cpp)
target_link_libraries(
    FD
    ph_eq_wilson
    ph_eq
    cubic_eos_mixture
    ${cubic_eos}
)