
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

static inline uint64_t rdtsc(void) {
    unsigned int low, high;

    __asm__ volatile (
        "lfence\n\t"
        "rdtsc"
        : "=a"(low), "=d"(high)
        :
        : "memory"
    );

    return ((uint64_t)high << 32) | low;
}

int main() {
    uint64_t start, end;
    volatile pid_t p;

    start = rdtsc();

    for (int i = 0; i < 100; i++) {
        p = getppid();
    }

    end = rdtsc();

    printf("Number of getppid() calls: 100\n");
    printf("Timestamp counter difference: %llu ticks\n", (unsigned long long)(end - start));

    return 0;
}
