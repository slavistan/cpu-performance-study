# Project: CPU-Performance-Study
# Author: Stanislaw Hüll

cmake_minimum_required(VERSION 3.14)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generate a compilation database

project(CPU-Performance-Study
  VERSION 0.0.1
  LANGUAGES CXX)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "")
  message(FATAL_ERROR "The build type must not be defined.\n \
This project relies on manual control of the compiler flags. Some targets \
must be built with optimizations while certain cache effects cannot be \
observed unless optimization is disabled.")
endif()

if( (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "clang") AND
    (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU") )
  message(FATAL_ERROR "Either GNU compiler or clang required. Your compiler is: ${CMAKE_CXX_COMPILER_ID}")
endif()

include(${PROJECT_SOURCE_DIR}/cmake/helpers.cmake)

set(CSVROOT "${PROJECT_SOURCE_DIR}/csv") # permanently stores benchmark results
set(SCRIPTSROOT "${PROJECT_SOURCE_DIR}/scripts") # provides some useful scripts
set(BENCHMARKSROOT "${PROJECT_SOURCE_DIR}/benchmarks")

# Allow the user to run pre- and post-benchmark commands.
set(BENCHMARK_PRE_CMD ${SCRIPTSROOT}/cpu-frequency-scaling.sh off
  CACHE STRING "Command to be executed prior to every benchmark.")
set(BENCHMARK_POST_CMD ${SCRIPTSROOT}/cpu-frequency-scaling.sh on
  CACHE STRING "Command to be executed after every benchmark.")

add_subdirectory(csv)        # Results
add_subdirectory(benchmarks) # Benchmark sources
add_subdirectory(slides)     # Presentation

