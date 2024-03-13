#include <cstdio>
#include <unistd.h>

int main() {
    fprintf(stderr, "hi I'm the takeover! PID: %d\n", getpid());
}
