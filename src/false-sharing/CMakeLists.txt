cmake_minimum_required(VERSION 3.14)

## Target
# Generate the benchmark binary
find_package(benchmark REQUIRED)
find_package(OpenMP)

add_executable(false-sharing false-sharing.cpp)
target_compile_features(false-sharing PRIVATE cxx_std_20)
target_link_libraries(false-sharing PRIVATE benchmark::benchmark OpenMP::OpenMP_CXX)
target_compile_options(false-sharing PRIVATE -O0)

## Target
# Run the benchmark and save raw output to CSV
set(RAWCSV_PATH "${CMAKE_CURRENT_BINARY_DIR}/rawdata.csv")
add_custom_target(
  false-sharing-run-benchmark
  DEPENDS false-sharing
  BYPRODUCTS ${RAWCSV_PATH}
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/run-benchmark.sh
    $<TARGET_FILE:false-sharing>
    ${RAWCSV_PATH})

## Target
# Prepare raw data for analysis
set(CSV_PATH "${CMAKE_CURRENT_BINARY_DIR}/data.csv")
add_custom_target(
false-sharing-prepare-data
DEPENDS ${RAWCSV_PATH}
BYPRODUCTS ${CSV_PATH}
COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/prepare-data.sh
  ${RAWCSV_PATH}
  ${CSV_PATH})

## Target
# Generate a report from the CSV
set(REPORT_PATH "${CMAKE_CURRENT_BINARY_DIR}/report.png")
add_custom_target(
  false-sharing-generate-report
  DEPENDS ${CSV_PATH}
  BYPRODUCTS ${REPORT_PATH}
  COMMAND Rscript ${CMAKE_CURRENT_SOURCE_DIR}/generate-report.R
    ${CSV_PATH}
    ${REPORT_PATH})

# Copy files into build directory for ease of debugging
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run-benchmark.sh ${CMAKE_CURRENT_BINARY_DIR}/run-benchmark.sh COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/generate-report.R ${CMAKE_CURRENT_BINARY_DIR}/generate-report.R COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/prepare-data.sh ${CMAKE_CURRENT_BINARY_DIR}/prepare-data.sh COPYONLY)
