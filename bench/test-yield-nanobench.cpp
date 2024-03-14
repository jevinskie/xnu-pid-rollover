#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>
using namespace ankerl;

extern "C" {
#include <mach/mach_traps.h>
}
#include <pthread/sched.h>
#include <unistd.h>

static void BM_test_sched_yield() {
    nanobench::Bench().run("test_sched_yield", [&]() {
        nanobench::doNotOptimizeAway(sched_yield());
    });
}

static void BM_test_swtch() {
    nanobench::Bench().run("test_swtch", [&]() {
        nanobench::doNotOptimizeAway(swtch());
    });
}

static void BM_test_swtch_pri() {
    nanobench::Bench().run("test_swtch_pri", [&]() {
        nanobench::doNotOptimizeAway(swtch_pri(0));
    });
}

static void BM_test_usleep() {
    nanobench::Bench().run("test_usleep", [&]() {
        nanobench::doNotOptimizeAway(usleep(1'000));
    });
}

int main(void) {
    BM_test_sched_yield();
    BM_test_swtch();
    BM_test_swtch_pri();
    BM_test_usleep();
    return 0;
}
