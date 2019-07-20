cmake_minimum_required(VERSION 3.14)

## Target
# Generate the benchmark binary
find_package(benchmark REQUIRED)
add_executable(col-vs-row-major col-vs-row-major.cpp)
target_compile_features(col-vs-row-major PRIVATE cxx_std_20)
target_link_libraries(col-vs-row-major PRIVATE benchmark::benchmark)
target_compile_options(col-vs-row-major PRIVATE "-O0")

function(register_benchmark arg_target)

  # Parse named arguments and set defaults.
  cmake_parse_arguments(arg "" "SCRIPT;CSV;RAWCSV;CSVDIR" "" ${ARGN})

  if(NOT DEFINED arg_csv)
    set(arg_csv ${CMAKE_CURRENT_BINARY_DIR}/formatted-data.csv)
  endif()
  if(NOT DEFINED arg_rawcsv)
    set(arg_rawcsv ${CMAKE_CURRENT_BINARY_DIR}/raw-data.raw)
  endif()
  if(NOT DEFINED arg_script)
    set(arg_script ${CMAKE_CURRENT_SOURCE_DIR}/benchmark.sh)
  endif()
  if(NOT DEFINED arg_csvdir)
    set(arg_csvdir ${CSVROOT}/${arg_target})
  endif()

  # Sanity-check all parameters.
  if(NOT (EXISTS ${arg_script}))
    message(FATAL_ERROR "File '${arg_script}' does not exist.")
  elseif(NOT (IS_ABSOLUTE ${arg_csv}
              AND IS_ABSOLUTE ${arg_rawcsv}
              AND IS_ABSOLUTE ${arg_csvdir}
              AND IS_ABSOLUTE ${arg_script}))
    message(FATAL_ERROR "Paths must be absolute.")
  elseif(NOT TARGET ${arg_target})
    message(FATAL_ERROR "Target '${arg_target}' does not exist.")
  endif()

  # Register target which will run the benchmark. The script will be invoked as
  # '> /path/to/benchmark.sh run /path/to/binary /path/to/raw-output.csv'
  # Additionally, the benchmark script script is symlinked into the build directory
  # for the ease of debugging.
  get_filename_component(script_tail ${arg_script} NAME)
  add_custom_target(${arg_target}-run
    DEPENDS ${arg_target}
    BYPRODUCTS ${arg_rawcsv}
    COMMAND ${CMAKE_COMMAND} -E
      create_symlink ${arg_script} ${CMAKE_CURRENT_BINARY_DIR}/${script_tail}
    COMMAND ${BENCHMARK_PRE_CMD}
    COMMAND ${arg_script} run $<TARGET_FILE:${arg_target}> ${arg_rawcsv}
    COMMAND ${BENCHMARK_POST_CMD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  # Register target which will add information to the benchmark's output and
  # will apply formatting. The script will be invoked as
  # '> /path/to/benchmark.sh format /path/to/raw-output.csv /path/to/prepared-output.csv'
  # Additionally, store the formatted output permanently.
  execute_process(
    COMMAND /usr/bin/sh -c "date +%Y-%m-%d-%H:%m:%S:%N"
    OUTPUT_VARIABLE timestamp)
  string(REGEX REPLACE "\n$" "" timestamp "${timestamp}") # remove trailing newlines
  set(unique-name "${arg_csvdir}/result-${timestamp}.csv")
  add_custom_target(${arg_target}-format
    DEPENDS ${arg_rawcsv}
    BYPRODUCTS ${arg_csv}
    COMMAND ${arg_script} format ${arg_rawcsv} ${arg_csv}
    COMMAND ${CMAKE_COMMAND} -E copy ${arg_csv} ${unique-name}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

  # Register target which will generate a report from the formatted data. The
  # script will be invoked as
  # '> /path/to/benchmark.sh report /path/to/formatted-data.csv /path/to/output'
  # Note that the second argument is a path to the directory where all output
  # files shall reside.
  add_custom_target(${arg_target}-report
    DEPENDS ${arg_csv}
    COMMAND ${arg_script} report ${arg_csv} ${CMAKE_CURRENT_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endfunction()

register_benchmark(col-vs-row-major)
# TODO: Add other targets/subdirs
