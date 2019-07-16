# Project: CPU-Performance-Study
# Author: Stanislaw Hüll
#
# This file contains the basic CMake setup of the C3srmatrix project. Targets
# are defined in 'src/CMakeLists.txt'.
#

## 1. Prologue
## ---------------------------------
cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # generate a compilation database
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

## 2. Project & Subdirectories
## --------------------------
project(CPU-Performance-Study
  VERSION 0.0.1
  LANGUAGES CXX)

add_subdirectory(src)
