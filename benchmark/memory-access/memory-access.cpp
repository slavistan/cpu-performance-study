#include <vector>
#include <iostream>
#include <sstream>
#include <chrono>
#include <algorithm>

#ifndef BUILD_TYPE
  #define BUILD_TYPE "UNKNOWN"
#endif

void displayWarning(const char * param)
{
  std::cerr << "Please enter a positive step size, e.g '" << param << " 10'" << std::endl;
}

int main(int argc, char** argv)
{
  //
  // Parse argument
  //
  if(argc != 2)
  {
    displayWarning(argv[0]);
    return 0;
  }
  int step_sz = 0;
  std::stringstream ss;
  ss << argv[1];
  ss >> step_sz;
  if(step_sz <= 0)
  {
    displayWarning(argv[0]);
    return 0;
  }
  //
  // Perform measurement
  //
  auto data = std::vector<int>(64 * 1024 * 1024);
  std::generate(data.begin(), data.end(), [index = (int)0]() mutable { return ++index; });
  using namespace std::chrono;
  const auto start = high_resolution_clock::now();

  for(auto ii = 0u; ii < data.size(); ii += step_sz)
  {
    data[ii] *= 3;
  }
  const auto finish = high_resolution_clock::now();
  // Observe data
  if(data.back() == 17) std::cout << "This will never happen" << std::endl;
  auto duration = duration_cast<microseconds>(finish - start).count();
  std::cout << "  - step_sz = " << step_sz << std::endl
            << "  - duration_us = " << duration << std::endl
            << "  - build_type = " << BUILD_TYPE << std::endl;
  return 0;
}
