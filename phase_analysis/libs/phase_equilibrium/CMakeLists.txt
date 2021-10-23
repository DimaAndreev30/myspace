add_library(ph_eq_wilson wilson.cpp)

add_library(ph_eq_two_phase_compos two_phase_compos.cpp)

add_library(ph_eq solver.cpp)
target_link_libraries(ph_eq ph_eq_two_phase_compos)
