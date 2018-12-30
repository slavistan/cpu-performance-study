add_executable(memory-access memory-access.cpp)

target_compile_definitions(memory-access PRIVATE BUILD_TYPE="${CMAKE_BUILD_TYPE}")

set_target_properties(memory-access
  PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF)

