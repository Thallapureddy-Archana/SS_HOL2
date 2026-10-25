#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig) {
    const char msg[] = "SIGSEGV caught. Exiting safely.\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(1);
}

int main() {
    signal(SIGSEGV, handler);

    printf("Raising SIGSEGV for demonstration...\n");
    fflush(stdout);
    raise(SIGSEGV);

    return 0;
}
