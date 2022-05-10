add_library(phan_FD_mixture_factory mixture_factory.cpp)
target_link_libraries(
    phan_FD_mixture_factory
    phan_cubic_eos
)
