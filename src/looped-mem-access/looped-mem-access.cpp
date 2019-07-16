// TODO: Debug build does not show expected results. Instead, the duration does
//       scale according to the chosen stride. Why is that? What's there to
//       optimize around a simple for loop?

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

// Size should be considerable larger than any cache to ensure that most of the
// time accessing the array requires a memory load from RAM.
constexpr auto SIZE = 128 * 1024 * 1024;

// Choose stride and type such that incrementing the counter guarantees that
// a new cache line will be accessed. My i7 has a cache line size of
// 8 x 8 = 64 bytes.
constexpr auto STRIDE = 8;
using T = uint64_t;

void dense_loop(benchmark::State& state) {

  auto vec = std::vector<T>(SIZE, 7);
  for (auto _: state) {
    for (std::size_t ii = 0; ii < vec.size(); ii++) {
      benchmark::DoNotOptimize(vec[ii] += 3);
    }
  }
}

void stridden_loop(benchmark::State& state) {

  auto vec = std::vector<T>(SIZE, -7); 
  for (auto _: state) {
    for (std::size_t ii = 0; ii < vec.size(); ii += STRIDE) {
      benchmark::DoNotOptimize(vec[ii] += 3);
    }
  }
}

BENCHMARK(stridden_loop);
BENCHMARK(dense_loop);

BENCHMARK_MAIN();
