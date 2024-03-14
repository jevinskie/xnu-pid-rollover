#include <cstdio>
#include <ctime>
#include <unistd.h>

constexpr struct timespec ts_10ms {
    .tv_sec = 0, .tv_nsec = 10'000'000,
};

int main() {
    fprintf(stderr, "nop-looper PID: %d\n", getpid());
    while (true) {
        nanosleep(&ts_10ms, nullptr);
    }
}
