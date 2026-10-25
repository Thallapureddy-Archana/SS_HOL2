
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    printf("SIGSTOP received!\n");
}

int main() {
    signal(SIGSTOP, handler);

    printf("Receiver PID: %ld\n", (long)getpid());
    printf("Waiting for signals...\n");
    fflush(stdout);

    while (1) {
        pause();
    }

    return 0;
}
