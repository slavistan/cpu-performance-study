#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <algorithm>

int main(int argc, char** argv)
{
  //
  // Parse argument
  //
  int array_sz_in_kb = 0;
  std::stringstream ss(argv[1]);
  ss >> array_sz_in_kb;

  //
  // Perform measurement
  //
  // Init array
  auto data = std::vector<int>(array_sz_in_kb * 1000 / sizeof(int));
  std::generate(data.begin(), data.end(), [index = (int)0]() mutable { return ++index; });

  using namespace std::chrono;
  const auto start = high_resolution_clock::now();

  const auto iterations = 100;
  const auto cache_line_sz_in_bytes = 64;
  for(int ii = 0; ii < iterations; ++ii)
  {
    // touch every cache line
    for(auto jj = 0u; jj < data.size(); jj += cache_line_sz_in_bytes / sizeof(int))
    {
      data[jj]++;
    }
  }
  const auto finish = high_resolution_clock::now();
  // Observe data
  if(data.back() == 17) std::cout << "This will never happen" << std::endl;

  auto duration = duration_cast<nanoseconds>(finish - start).count();
  const auto duration_per_element = duration / ((double)iterations * (double)data.size());
  std::cout << "  - array_sz_in_kb = " << array_sz_in_kb << std::endl
            << "  - duration_ns_per_elem = " << duration_per_element << std::endl
            << "  - build_type = " << BUILD_TYPE << std::endl;
  return 0;
}
