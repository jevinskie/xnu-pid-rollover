#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>
using namespace ankerl;
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wunused-parameter"
// #pragma GCC diagnostic push
// #pragma GCC diagnostic ignored "-Wdeprecated-copy"
#include <subprocess/subprocess.h>
// #pragma GCC diagnostic pop pop
// namespace sp = subprocess;

#include <cstdlib>

static void BM_test_pid_kill() {
    nanobench::Bench().run("test_pid_kill", [&]() {
        nanobench::doNotOptimizeAway(rand());
    });
}

int main(void) {

    BM_test_pid_kill();

    return 0;
}
