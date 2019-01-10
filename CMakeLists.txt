##
## Boilerplate Code
##

cmake_minimum_required(VERSION 3.11)

# Enable maximum level of error warnings
option(DEVELOPER_MODE "Increases compiler verbosity and raises warnings to errors" OFF)
if(DEVELOPER_MODE)
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy"
    )
  if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found")
  else()
    message(STATUS "clang-tiidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY
      "${CLANG_TIDY_EXE}" "-checks='bugprone*,cppcoreguidelines*,cert*,google*,hicpp*,llvm*,misc*,modernize*,performance*,readability*"
      "-header-filter=*")

  endif()

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
