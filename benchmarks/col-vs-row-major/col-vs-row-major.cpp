// Measure performance drop due to a mismatched memory access scheme. We create
// a rowmajor matrix in memory and measure the latency for accesses using a
// colmajor and rowmajor scheme.
#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

void rowmajor(benchmark::State& state) {
  const auto dim = state.range(0);
  auto vec = std::vector<double>(uint64_t(dim) * dim);
  for ([[maybe_unused]] auto _: state) {
    for(uint64_t y = 0; y < dim; y += 1) {
      for(uint64_t x = 0; x < dim; x += 1) {

        const auto index = x + dim * y;
        vec[index] += 3;
      }
    }
  }
}

void colmajor(benchmark::State& state) {
  const auto dim = state.range(0);
  auto vec = std::vector<double>(uint64_t(dim) * dim);
  for ([[maybe_unused]] auto _: state) {
    for(uint64_t y = 0; y < dim; y += 1) {
      for(uint64_t x = 0; x < dim; x += 1) {

        const auto index = y + dim * x;
        vec[index] += 3;
      }
    }
  }
}

constexpr auto MAX = 15;
BENCHMARK(rowmajor)->RangeMultiplier(2)->Range(8, 1 << MAX);
BENCHMARK(colmajor)->RangeMultiplier(2)->Range(8, 1 << MAX);

BENCHMARK_MAIN();
