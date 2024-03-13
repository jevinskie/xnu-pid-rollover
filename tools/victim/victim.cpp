#include <cstdio>
#include <unistd.h>

int main() {
    fprintf(stderr, "hi I'm the victim! PID: %d\n", getpid());
    unsigned int i = 0;
    while (true) {
        fprintf(stderr, "sleeping 1 section, iteration %u\n", i);
        usleep(1'000'000);
        ++i;
    }
}
