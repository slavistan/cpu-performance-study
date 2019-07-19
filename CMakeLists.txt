# Project: CPU-Performance-Study
# Author: Stanislaw Hüll

## 1. Prologue
## ---------------------------------
cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generate a compilation database
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

## 2. Project & Subdirectories
## --------------------------
project(CPU-Performance-Study
  VERSION 0.0.1
  LANGUAGES CXX)

if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "")
  message(FATAL_ERROR "The build type must not be defined.\n \
This project relies on manual control of the compiler flags. Some targets \
must be built with optimizations while certain cache effects cannot be \
observe unless optimization is disabled.")
endif()

if( (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "clang") AND (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"))
  message(FATAL_ERROR "Either GNU compiler or clang required. Your compiler is: ${CMAKE_CXX_COMPILER_ID}")
endif()

add_subdirectory(src)
add_subdirectory(slides)
