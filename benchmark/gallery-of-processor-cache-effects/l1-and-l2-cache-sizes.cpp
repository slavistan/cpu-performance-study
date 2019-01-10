#include <algorithm>
#include <chrono>
#include <exception>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

int main(int /*argc*/, char* argv[])
{
  //
  // Parse arguments
  //
  int array_sz_in_kb;
  try
  {
    array_sz_in_kb = std::stoi(*std::next(argv));
  }
  catch (...)
  {
    std::cout << "Usage: " << *argv << " <array size in kilobytes>"  << std::endl;
    return 0;
  }
  //
  // Perform measurement
  //
  auto data = std::vector<int>(array_sz_in_kb * 1000 / sizeof(int));
  std::generate(data.begin(), data.end(), [index = 0]() mutable { return ++index; });

  const auto start = high_resolution_clock::now();

  const auto niteration = 100;
  const auto cache_line_sz_in_bytes = 64;
  for(int ii = 0; ii < niteration; ++ii)
  {
    // touch every cache line
    for(auto jj = 0u; jj < data.size(); jj += cache_line_sz_in_bytes / sizeof(int))
    {
      data[jj]++;
    }
  }
  const auto finish = high_resolution_clock::now();
  // Observe data
  if(data.back() == 17)
  {
    std::cout << "This will never happen" << std::endl;
  }

  auto duration = duration_cast<nanoseconds>(finish - start).count();
  const auto duration_per_element = static_cast<double>(duration) / (niteration * data.size());
  std::cout << "  - array_sz_in_kb = " << array_sz_in_kb << std::endl
            << "  - duration_ns_per_elem = " << duration_per_element << std::endl;
  return 0;
}
