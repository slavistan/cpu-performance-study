cmake_minimum_required(VERSION 3.14)

## Target
# Generate the benchmark binary
find_package(benchmark REQUIRED)
add_executable(col-vs-row-major col-vs-row-major.cpp)
target_compile_features(col-vs-row-major PRIVATE cxx_std_20)
target_link_libraries(col-vs-row-major PRIVATE benchmark::benchmark)
target_compile_options(col-vs-row-major PRIVATE "-O0")

register_benchmark(col-vs-row-major)
