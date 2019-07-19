cmake_minimum_required(VERSION 3.14)

## Target
# Generate the benchmark binary
find_package(benchmark REQUIRED)
add_executable(looped-mem-access looped-mem-access.cpp)
target_compile_features(looped-mem-access PRIVATE cxx_std_20)
target_link_libraries(looped-mem-access PRIVATE benchmark::benchmark)
target_compile_options(looped-mem-access PRIVATE -O3 -DNDEBUG)

## Target - run manually
# Run the benchmark and save results to CSV
set(CSV_PATH "${CMAKE_CURRENT_BINARY_DIR}/data.csv")
add_custom_target(
  looped-mem-access-run-benchmark
  DEPENDS looped-mem-access
  BYPRODUCTS ${CSV_PATH}
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run-benchmark.sh
    $<TARGET_FILE:looped-mem-access>
    ${CSV_PATH})

## Target - run manually
# Generate a report from the CSV
set(REPORT_PATH "${CMAKE_CURRENT_BINARY_DIR}/report.png")
add_custom_target(
  looped-mem-access-generate-report
  DEPENDS ${CSV_PATH}
  BYPRODUCTS ${REPORT_PATH}
  COMMAND Rscript ${CMAKE_CURRENT_SOURCE_DIR}/generate-report.R
    ${CSV_PATH}
    ${REPORT_PATH})
