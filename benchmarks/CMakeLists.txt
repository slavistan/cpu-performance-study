# TODO: Create a directory inside 'csv/' to permanently store benchmark results.

file(GLOB subdirs LIST_DIRECTORIES true *)
foreach(fulldir ${subdirs})
  get_filename_component(dir ${fulldir} NAME)
  if(NOT ${dir} STREQUAL "CMakeLists.txt")
    add_subdirectory(${dir})
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/csv/${dir})
  endif()
endforeach()
