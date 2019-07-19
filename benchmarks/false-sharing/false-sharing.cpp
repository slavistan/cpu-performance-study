// Demonstrate false sharing
#include <benchmark/benchmark.h>

#include <omp.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

void falsesharing(benchmark::State& state) {

  auto vec = std::vector<uint64_t>(4032000, 1); // 40320 == 8!
  const auto numThreads = state.range(0);
  auto partial = std::vector<uint64_t>(numThreads);

  for (auto _: state) {
    #pragma omp parallel num_threads(numThreads)
    {
      const auto workLoad = vec.size() / numThreads;
      const auto threadId = omp_get_thread_num();
      for(uint64_t ii = workLoad * threadId; ii < workLoad * (threadId + 1); ++ii) {
        partial[threadId] += vec[ii];
      }
    }
    benchmark::DoNotOptimize(std::accumulate(partial.begin(), partial.end(), uint64_t(0)));
  }
}

void nosharing(benchmark::State& state) {

  auto vec = std::vector<uint64_t>(4032000, 1); // 40320 == 8!
  const auto numThreads = state.range(0);
  auto partial = std::vector<uint64_t>(numThreads);

  for (auto _: state) {
    #pragma omp parallel num_threads(numThreads)
    {
      const auto workLoad = vec.size() / numThreads;
      const auto threadId = omp_get_thread_num();
      auto partialSum = uint64_t(0);
      for(uint64_t ii = workLoad * threadId; ii < workLoad * (threadId + 1); ++ii) {
        partialSum += vec[ii];
      }
      partial[threadId] = partialSum;
    }
    benchmark::DoNotOptimize(std::accumulate(partial.begin(), partial.end(), uint64_t(0)));
  }
}

#define MAXTHREADS 4
BENCHMARK(nosharing) -> DenseRange(1, MAXTHREADS, 1);
BENCHMARK(falsesharing) -> DenseRange(1, MAXTHREADS, 1);

BENCHMARK_MAIN();
