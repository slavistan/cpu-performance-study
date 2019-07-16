cmake_minimum_required(VERSION 3.14)

find_package(benchmark REQUIRED)
add_executable(looped-mem-access looped-mem-access.cpp)
target_compile_features(looped-mem-access PRIVATE cxx_std_20)
target_link_libraries(looped-mem-access PRIVATE benchmark::benchmark)
