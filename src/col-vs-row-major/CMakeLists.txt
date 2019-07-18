cmake_minimum_required(VERSION 3.14)

## Target
# Generate the benchmark binary
find_package(benchmark REQUIRED)
add_executable(col-vs-row-major col-vs-row-major.cpp)
target_compile_features(col-vs-row-major PRIVATE cxx_std_20)
target_link_libraries(col-vs-row-major PRIVATE benchmark::benchmark)
target_compile_options(col-vs-row-major PRIVATE "-O0")

## Target
# Run the benchmark and save raw output to CSV
set(RAWCSV_PATH "${CMAKE_CURRENT_BINARY_DIR}/rawdata.csv")
add_custom_target(
  col-vs-row-major-run-benchmark
  DEPENDS col-vs-row-major
  BYPRODUCTS ${RAWCSV_PATH}
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run-benchmark.sh
    $<TARGET_FILE:col-vs-row-major>
    ${RAWCSV_PATH})

## Target
# Prepare raw data for analysis
set(CSV_PATH "${CMAKE_CURRENT_BINARY_DIR}/data.csv")
add_custom_target(
col-vs-row-major-prepare-data
DEPENDS ${RAWCSV_PATH}
BYPRODUCTS ${CSV_PATH}
COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/prepare-data.sh
  ${RAWCSV_PATH}
  ${CSV_PATH})

## Target - run manually
# Generate a report from the CSV
set(REPORT_PATH "${CMAKE_CURRENT_BINARY_DIR}/report.png")
add_custom_target(
  col-vs-row-major-generate-report
  DEPENDS ${CSV_PATH}
  BYPRODUCTS ${REPORT_PATH}
  COMMAND Rscript ${CMAKE_CURRENT_SOURCE_DIR}/generate-report.R
    ${CSV_PATH}
    ${REPORT_PATH})

# Copy files into build directory for ease of debugging
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run-benchmark.sh ${CMAKE_CURRENT_BINARY_DIR}/run-benchmark.sh COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/generate-report.R ${CMAKE_CURRENT_BINARY_DIR}/generate-report.R COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/prepare-data.sh ${CMAKE_CURRENT_BINARY_DIR}/prepare-data.sh COPYONLY)
