
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <errno.h>

int main() {
    struct rlimit limit;
    struct sysinfo info;

    printf("a. Maximum argument/environment size: %ld bytes\n", sysconf(_SC_ARG_MAX));
    printf("b. Maximum simultaneous processes per user ID: %ld\n", sysconf(_SC_CHILD_MAX));
    printf("c. Clock ticks per second: %ld\n", sysconf(_SC_CLK_TCK));

    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        if (limit.rlim_cur == RLIM_INFINITY)
            printf("d. Soft open-file limit: Unlimited\n");
        else
            printf("d. Soft open-file limit: %llu\n", (unsigned long long)limit.rlim_cur);
    } 
    else {
        write(2,"getrlimit error\n", 16);
    }

    printf("e. Page size: %ld bytes\n", sysconf(_SC_PAGESIZE));

    unsigned long long unit = info.mem_unit;
    unsigned long long total_bytes = (unsigned long long)info.totalram * unit;
    unsigned long long free_bytes = (unsigned long long)info.freeram * unit;

    printf("f. Total physical memory pages: %llu\n", total_bytes / sysconf(_SC_PAGESIZE));
    printf("g. Free physical memory pages: %llu\n", free_bytes / sysconf(_SC_PAGESIZE));

    return 0;
}
