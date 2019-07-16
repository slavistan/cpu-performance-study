#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <string>
#include <type_traits>
#include <vector>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

int main(int /*argc*/, char** argv)
{
  int blocked_loop;
  try
  {
    blocked_loop = std::stoi(*std::next(argv));
  }
  catch (...)
  {
    std::cout << "Usage: " << *argv << " <1|0 - use block loop>" << std::endl;
    return 0;
  }

  // Number of loop iterations
  const auto array_sz = 1e8;
  auto data = std::vector<double>(array_sz, 4.97);

  // Setup timers
  const auto start = high_resolution_clock::now();
  if(blocked_loop != 0)
  {
    for(auto ii = 0; ii < array_sz - 14; ii += 15)
    {
      data[0 + ii] += 3.14;
      data[1 + ii] += 3.14;
      data[2 + ii] += 3.14;
      data[3 + ii] += 3.14;
      data[4 + ii] += 3.14;
      data[5 + ii] += 3.14;
      data[6 + ii] += 3.14;
      data[7 + ii] += 3.14;
      data[8 + ii] += 3.14;
      data[9 + ii] += 3.14;
      data[10 + ii] += 3.14;
      data[11 + ii] += 3.14;
      data[12 + ii] += 3.14;
      data[13 + ii] += 3.14;
      data[14 + ii] += 3.14;
    }
  }
  else
  {
    for(auto ii = 0; ii < array_sz; ++ii)
    {
      data[ii] += 3.14;
    }
  }
  const auto finish = high_resolution_clock::now();

  auto duration_us = duration_cast<microseconds>(finish - start).count();
  std::cout << "blocked_loop = " << blocked_loop << std::endl;
  std::cout << "duration_us = " << duration_us << std::endl;
  return 0;
}
