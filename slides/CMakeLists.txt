cmake_minimum_required(VERSION 3.14)

add_custom_target(slides
  COMMAND ${CMAKE_COMMAND} -E "configure_file($<TARGET_FILE:col-vs-row-major> ${CMAKE_CURRENT_SOURCE_DIR}/dingo)")

