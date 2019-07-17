cmake_minimum_required(VERSION 3.14)

# Generate the benchmark binary
find_package(benchmark REQUIRED)
add_executable(looped-mem-access looped-mem-access.cpp)
target_compile_features(looped-mem-access PRIVATE cxx_std_20)
target_link_libraries(looped-mem-access PRIVATE benchmark::benchmark)

# Add custom command to generate a report

set(CSVDATA "data.csv")
add_custom_command(
  OUTPUT ${CSVDATA}
  DEPENDS looped-mem-access
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/generate-data.sh 
    $<TARGET_FILE:looped-mem-access>
    ${CMAKE_CURRENT_BINARY_DIR}/${CSVDATA})

add_custom_target(
  generate-csvdata ALL
  DEPENDS ${CSVDATA}
  COMMENT "> generate-csvdata: Outfile: '${CMAKE_CURRENT_BINARY_DIR}/${CSVDATA}'")

set(PLOT "plot.png")
add_custom_command(
  OUTPUT ${PLOT}
  DEPENDS generate-csvdata
  COMMAND Rscript ${CMAKE_CURRENT_SOURCE_DIR}/plot-raw-data.R
    ${CMAKE_CURRENT_BINARY_DIR}/${CSVDATA}
    ${CMAKE_CURRENT_BINARY_DIR}/${PLOT})

add_custom_target(
  generate-plot ALL
  DEPENDS ${PLOT}
  COMMENT "> generate-plot: Outfile: '${CMAKE_CURRENT_BINARY_DIR}/${PLOT}'")

# set(REPORT "analysis.pdf")
# add_custom_command(
#   OUTPUT ${REPORT}
#   DEPENDS generate-data
#   COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/analyze.sh
#     ${CMAKE_CURRENT_BINARY_DIR}/${RAW_DATA} # data in
#     ${CMAKE_CURRENT_BINARY_DIR}/${REPORT}   # report out
#   COMMENT "Analyzing gathered data")
# 
# add_custom_target(
#   analyze-data ALL
#   DEPENDS ${REPORT})
# Now define a target which depends on the command and causes it to be executed.
# See https://stackoverflow.com/questions/39960173/run-custom-shell-script-with-cmake

