#include <benchmark/benchmark.h>

extern "C" {
#include <mach/mach_traps.h>
}
#include <pthread/sched.h>
#include <unistd.h>

static void BM_test_sched_yield(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(sched_yield());
    }
}
BENCHMARK(BM_test_sched_yield)->ThreadRange(1, XNU_PID_ROLLOVER_NUM_CPUS);

static void BM_test_swtch(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(swtch());
    }
}
BENCHMARK(BM_test_swtch)->ThreadRange(1, XNU_PID_ROLLOVER_NUM_CPUS);

static void BM_test_swtch_pri(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(swtch_pri(0));
    }
}
BENCHMARK(BM_test_swtch_pri)->ThreadRange(1, XNU_PID_ROLLOVER_NUM_CPUS);

static void BM_test_usleep(benchmark::State &state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(usleep(1'000));
    }
}
BENCHMARK(BM_test_usleep)->ThreadRange(1, XNU_PID_ROLLOVER_NUM_CPUS);

BENCHMARK_MAIN();
