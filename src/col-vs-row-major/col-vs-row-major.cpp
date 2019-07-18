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
  const auto DIM = state.range(0);
  auto vec = std::vector<double>(static_cast<std::size_t>(DIM) * DIM);
  for (auto _: state) {
    for(uint64_t y = 0; y < DIM; y += 1) {
      for(uint64_t x = 0; x < DIM; x += 1) {
        
        const auto index = x + DIM * y;
        vec[index] += 3;
      }
    }
  }
}

void colmajor(benchmark::State& state) {
  const auto DIM = state.range(0);
  auto vec = std::vector<double>(static_cast<std::size_t>(DIM) * DIM);
  for (auto _: state) {
    for(uint64_t y = 0; y < DIM; y += 1) {
      for(uint64_t x = 0; x < DIM; x += 1) {
        
        const auto index = y + DIM * x;
        vec[index] += 3;
      }
    }
  }
}

#define MAX 15
BENCHMARK(rowmajor)->RangeMultiplier(2)->Range(8, 1 << MAX);
BENCHMARK(colmajor)->RangeMultiplier(2)->Range(8, 1 << MAX);

BENCHMARK_MAIN();
