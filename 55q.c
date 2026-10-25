#include <stdio.h>
#include <sys/resource.h>

int main() {
    struct rlimit limit;

    limit.rlim_cur = 1024 * 1024;
    limit.rlim_max = 1024 * 1024;

    setrlimit(RLIMIT_FSIZE, &limit);
    getrlimit(RLIMIT_FSIZE, &limit);

    printf("Soft limit: %llu bytes\n",(unsigned long long)limit.rlim_cur);
    printf("Hard limit: %llu bytes\n",(unsigned long long)limit.rlim_max);

    return 0;
}
