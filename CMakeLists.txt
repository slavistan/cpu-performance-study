##
## Boilerplate Code
##

cmake_minimum_required(VERSION 3.11)

# Enable maximum level of error warnings
option(DEVELOPER_MODE "Increases compiler verbosity and raises warnings to errors" OFF)
if(DEVELOPER_MODE)
  if(MSVC)
    add_compile_options(/W3 /Wx)
  else()
    add_compile_options(-Wall -Wpedantic -Werror)
  endif()
endif()

# Declare project
project(cpu-performance-study)

# Put all executables into the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

##
## End of Boilerplate code
##

add_subdirectory(benchmark)
