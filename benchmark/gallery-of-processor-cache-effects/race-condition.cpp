//
// Compare execution speed of for_each in parallel/sequential mode writing a atomic/non-atomic counter.
//
#include <atomic>
#include <chrono>
#include <iostream>
#include <pstl/algorithm>
#include <pstl/execution>
#include <pstl/numeric>
#include <vector>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main(int /*argc*/, char** argv)
{
  // Parse input
  uint64_t sz = 10000000;
  try
  {
    sz = std::strtol(*std::next(argv), nullptr, 0);
  }
  catch (...)
  {
    std::cout << "Usage: " << *argv << " <size of array>" << std::endl;
    return 0;
  }

  // Fill array with values. Avoid usage of overly trivial values (compiler might smell a rat).
  auto data = std::vector<double>(sz);
  std::generate(data.begin(), data.end(), [ii = 1]() mutable { return ii++; });

  {
    // Non-atomic counter + parallel execution
    auto counter = 0;
    const auto start = high_resolution_clock::now();
    std::for_each(std::execution::par,
                  data.begin(),
                  data.end(),
                  [&counter](auto elem) { if (elem > 0) { counter++; } });
    const auto finish = high_resolution_clock::now();
    const auto duration = duration_cast<milliseconds>(finish - start).count();
    std::cout << "[Non-atomic; parallel]: Counter: " << counter << "/" << sz << " = "
              <<  static_cast<double>(counter)/sz * 100 << "%. [" << duration << " ms]"
              << std::endl;
  }
  {
    // Non-atomic counter + sequential execution
    auto counter = 0;
    const auto start = high_resolution_clock::now();
    std::for_each(std::execution::seq,
                  data.begin(),
                  data.end(),
                  [&counter](auto elem) { if (elem > 0) { counter++; } });
    const auto finish = high_resolution_clock::now();
    const auto duration = duration_cast<milliseconds>(finish - start).count();
    std::cout << "[Non-atomic; sequential]: Counter: " << counter << "/" << sz << " = "
              <<  static_cast<double>(counter)/sz * 100 << "%. [" << duration << " ms]"
              << std::endl;
  }
  {
    // Atomic counter + parallel execution
    auto counter = std::atomic<int>(0);
    const auto start = high_resolution_clock::now();
    std::for_each(std::execution::par,
                  data.begin(),
                  data.end(),
                  [&counter](auto elem) { if (elem > 0) { counter++; } });
    const auto finish = high_resolution_clock::now();
    const auto duration = duration_cast<milliseconds>(finish - start).count();
    std::cout << "[Atomic; parallel]: Counter: " << counter << "/" << sz << " = "
              <<  static_cast<double>(counter)/sz * 100 << "%. [" << duration << " ms]"
              << std::endl;
  }
  {
    // Atomic counter + sequential execution
    auto counter = std::atomic<int>(0);
    const auto start = high_resolution_clock::now();
    std::for_each(std::execution::seq,
                  data.begin(),
                  data.end(),
                  [&counter](auto elem) { if (elem > 0) { counter++; } });
    const auto finish = high_resolution_clock::now();
    const auto duration = duration_cast<milliseconds>(finish - start).count();
    std::cout << "[Atomic; sequential]: Counter: " << counter << "/" << sz << " = "
              <<  static_cast<double>(counter)/sz * 100 << "%. [" << duration << " ms]"
              << std::endl;
  }
}
