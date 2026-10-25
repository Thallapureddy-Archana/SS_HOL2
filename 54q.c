#include <stdio.h>
#include <sys/resource.h>

void print_limit(const char *name, int resource) {
    
    struct rlimit limit;
    etrlimit(resource, &limit);

    printf("\n%s\n", name);

    if (limit.rlim_cur == RLIM_INFINITY)
        printf("Soft limit: Unlimited\n");
    else
        printf("Soft limit: %llu\n", (unsigned long long)limit.rlim_cur);

    if (limit.rlim_max == RLIM_INFINITY)
        printf("Hard limit: Unlimited\n");
    else
        printf("Hard limit: %llu\n", (unsigned long long)limit.rlim_max);
}

int main() {
    print_limit("Maximum open files", RLIMIT_NOFILE);
    print_limit("Maximum file size", RLIMIT_FSIZE);
    print_limit("Maximum CPU time", RLIMIT_CPU);
    print_limit("Maximum stack size", RLIMIT_STACK);
    print_limit("Maximum data size", RLIMIT_DATA);
    print_limit("Maximum core file size", RLIMIT_CORE);
    return 0;
}
