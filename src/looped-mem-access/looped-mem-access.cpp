// #include <benchmark/benchmark.h>

#include <cstdint>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

auto data() {

  auto vec = std::vector<uint64_t>(1024 * 1024 * 1024, 7);
  std::generate(vec.begin(), vec.end(), [i = (int)0] () mutable { return ++i; });
  return vec;
}

// static void dense_loop(benchmark::State& state) {
// 
//   auto vec = data();
//   for (auto _: state) {
//     for (auto ii = 0; ii < vec.size(); ii++) {
//       benchmark::DoNotOptimize(vec[ii] += 3);
//     }
//   }
// 
//   benchmark::DoNotOptimize(std::accumulate(vec.begin(), vec.end(), 0.0));
// }
// 
// static void stridden_loop(benchmark::State& state) {
// 
//   auto vec = data();
//   for (auto _: state) {
//     for (auto ii = 0; ii < vec.size(); ii += 2) {
//       benchmark::DoNotOptimize(vec[ii] += 3);
//     }
//   }
// 
//   benchmark::DoNotOptimize(std::accumulate(vec.begin(), vec.end(), 0.0));
// }
// 
// BENCHMARK(dense_loop);
// BENCHMARK(stridden_loop);
// 
// BENCHMARK_MAIN();

int main() {

  auto vec = data();
  for (uint64_t ii = 0; ii < vec.size(); ii++) {
    vec[ii] += ii;
  }

  std::cout << "bananarama" << vec.back() << vec.front() << std::endl;
  // std::cout << "Acc = " << std::accumulate(vec.begin(), vec.end(), static_cast<uint64_t>(0)) << std::endl;

}
