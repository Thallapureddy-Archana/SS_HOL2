
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig) {
    const char msg[] = "SIGSEGV received. Exiting.\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    _exit(1);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);
    printf("Raising SIGSEGV for demonstration.\n");
    fflush(stdout);

    raise(SIGSEGV);

    return 0;
}
