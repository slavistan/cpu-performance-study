cmake_minimum_required(VERSION 3.14)

# Generate the benchmark binary
find_package(benchmark REQUIRED)
add_executable(looped-mem-access looped-mem-access.cpp)
target_compile_features(looped-mem-access PRIVATE cxx_std_20)
target_link_libraries(looped-mem-access PRIVATE benchmark::benchmark)

# Add custom command to generate a report
add_custom_command(
  # TODO: What does this OUTPUT mean? It does not have to be the the output file's name
  OUTPUT report.txt
  # Run this command ...
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate-report.sh ${CMAKE_CURRENT_BINARY_DIR}
  # ... from inside this directory
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/)

# Now define a target which causes the command to be executed
# See https://stackoverflow.com/questions/39960173/run-custom-shell-script-with-cmake
add_custom_target(
  generate-report ALL
  DEPENDS report.stxt)

