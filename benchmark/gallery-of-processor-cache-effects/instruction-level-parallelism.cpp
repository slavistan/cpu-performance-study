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
  int ninstructions;
  try
  {
    ninstructions = std::stoi(*std::next(argv));
  }
  catch (...)
  {
    std::cout << "Usage: " << *argv << " <number of instructions>" << std::endl;
    return 0;
  }

  // Number of loop iterations
  const auto iterations = 1e8;
  auto data = std::vector<double>(10, 4.97);

  // Setup timers
  auto start = high_resolution_clock::now();
  auto finish = high_resolution_clock::now();

  start = high_resolution_clock::now();
  switch (ninstructions)
  {
    case 1:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
      }
      break;
    }
    case 2:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
      }
      break;
    }
    case 3:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
        data[2] -= 7.24;
      }
      break;
    }
    case 4:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
        data[2] -= 7.24;
        data[3] += 22.1;
      }
      break;
    }
    case 5:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
        data[2] -= 7.24;
        data[3] += 22.1;
        data[4] += 2.1;
      }
      break;
    }
    case 6:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
        data[2] -= 7.24;
        data[3] += 22.1;
        data[4] += 2.1;
        data[5] += 0.1;
      }
      break;
    }
    case 7:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
        data[2] -= 7.24;
        data[3] += 22.1;
        data[4] += 2.1;
        data[5] += 0.1;
        data[6] += 1.1;
      }
      break;
    }
    case 8:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
        data[2] -= 7.24;
        data[3] += 22.1;
        data[4] += 2.1;
        data[5] += 0.1;
        data[6] += 1.1;
        data[7] += 4.6;
      }
      break;
    }
    case 9:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
        data[2] -= 7.24;
        data[3] += 22.1;
        data[4] += 2.1;
        data[5] += 0.1;
        data[6] += 1.1;
        data[7] += 4.6;
        data[8] -= 9.6;
      }
      break;
    }
    case 10:
    {
      for(auto ii = 0; ii < iterations; ++ii)
      {
        data[0]++;
        data[1] += 3.14;
        data[2] -= 7.24;
        data[3] += 22.1;
        data[4] += 2.1;
        data[5] += 0.1;
        data[6] += 1.1;
        data[7] += 4.6;
        data[8] -= 9.6;
        data[9] += 4.4;
      }
      break;
    }
  }
  finish = high_resolution_clock::now();

  auto duration_us = duration_cast<microseconds>(finish - start).count();
  std::cout << "ninstructions = " << ninstructions << std::endl;
  std::cout << "duration_us = " << duration_us << std::endl;
  return 0;
}
