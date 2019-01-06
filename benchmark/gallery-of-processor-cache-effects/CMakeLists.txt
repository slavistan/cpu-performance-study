add_executable(impact-of-cache-lines impact-of-cache-lines.cpp)
target_compile_definitions(impact-of-cache-lines PRIVATE BUILD_TYPE="${CMAKE_BUILD_TYPE}")
set_target_properties(impact-of-cache-lines
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF)

add_executable(l1-and-l2-cache-sizes l1-and-l2-cache-sizes.cpp)
target_compile_definitions(l1-and-l2-cache-sizes PRIVATE BUILD_TYPE="${CMAKE_BUILD_TYPE}")
set_target_properties(l1-and-l2-cache-sizes
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF)
