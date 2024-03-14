#include <benchmark/benchmark.h>
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wunused-parameter"
#include <subprocess/subprocess.h>
// #pragma GCC diagnostic pop
// namespace sp = subprocess;

#include <cstdlib>

static void BM_test_pid_kill(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(rand());
    }
}

BENCHMARK(BM_test_pid_kill);

BENCHMARK_MAIN();
