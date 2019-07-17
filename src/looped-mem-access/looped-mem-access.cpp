// TODO: Debug build does not show expected results. Instead, the duration does
//       scale according to the chosen stride. Why is that? What's there to
//       optimize around a simple for loop?

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

// Size should be considerably larger than any cache to ensure that most memory
// accesses read from RAM.
constexpr auto SIZE = 128 * 1024;// * 1024;

// This name ('loop') is used inside the analysis script. Don't change it.
void loop(benchmark::State& state) {

  const auto stride = state.range(0);
  auto vec = std::vector<uint8_t>(SIZE, 7);
  for (auto _: state) {
    for (std::size_t ii = 0; ii < vec.size(); ii += stride) {
      benchmark::DoNotOptimize(vec[ii] += 3);
    }
  }
}

BENCHMARK(loop) -> DenseRange(1, 5, 1);

BENCHMARK_MAIN();
