#include <algorithm>
#include <chrono>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

int main(int /*argc*/, char** argv)
{
  //
  // Parse argument
  //
  int step_sz;
  try
  {
    step_sz = std::stoi(*std::next(argv));
  }
  catch (...)
  {
    std::cout << "Usage: " << *argv << " <step size>" << std::endl;
    return 0;
  }

  //
  // Perform measurement
  //
  auto data = std::vector<int>(64 * 1024 * 1024);
  std::generate(data.begin(), data.end(), [index = 0]() mutable { return ++index; });
  const auto start = high_resolution_clock::now();

  for(auto ii = 0u; ii < data.size(); ii += step_sz)
  {
    data[ii] *= 3;
  }
  const auto finish = high_resolution_clock::now();
  // Observe data
  if(data.back() == 17)
  {
    std::cout << "This will never happen" << std::endl;
  }
  auto duration = duration_cast<microseconds>(finish - start).count();
  std::cout << "  - step_sz = " << step_sz << std::endl
            << "  - duration_us = " << duration << std::endl
            << "  - build_type = " << BUILD_TYPE << std::endl;
  return 0;
}
