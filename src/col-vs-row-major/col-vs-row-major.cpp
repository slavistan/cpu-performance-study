// Measure performance drop due to a mismatched memory access scheme. We create
// a rowmajor matrix in memory and measure the latency for accesses using a 
// colmajor and rowmajor scheme.
#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

// Matrix dimension
constexpr uint64_t DIM = 10000;

void rowmajor(benchmark::State& state) {
  auto vec = std::vector<double>(DIM * DIM);
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
  auto vec = std::vector<double>(DIM * DIM);
  for (auto _: state) {
    for(uint64_t y = 0; y < DIM; y += 1) {
      for(uint64_t x = 0; x < DIM; x += 1) {
        
        const auto index = y + DIM * x;
        vec[index] += 3;
      }
    }
  }
}

BENCHMARK(rowmajor)->DenseRange(1, 1, 1);
BENCHMARK(colmajor)->DenseRange(1, 1, 1);

BENCHMARK_MAIN();
