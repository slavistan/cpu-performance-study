add_subdirectory(col-vs-row-major)

  # add_benchmark:
  #
  # file(GLOB subdirs LIST_DIRECTORIES true *)
  # foreach(fulldir ${subdirs})
  #   get_filename_component(dir ${fulldir} NAME)
  #   if(NOT ${dir} STREQUAL "CMakeLists.txt")
  #     add_subdirectory(${dir})
  #     file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/csv/${dir})
  #   endif()
# endforeach()
