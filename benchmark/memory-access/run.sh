binary_release="../../build/memory-access"
binary_debug="../../build_debug/memory-access"
minstructor -o ./raw_data -f -n 25 "${binary_release} range(1,128,1)"
minstructor -o ./raw_data -f -n 25 "${binary_debug} range(1,128,1)"
