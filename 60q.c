
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    signal(SIGINT, SIG_IGN);

    printf("SIGINT is ignored for 10 seconds.\n");
    printf("Press Ctrl+C during this time.\n");
    sleep(10);

    signal(SIGINT, SIG_DFL);

    printf("Default SIGINT action restored.\n");
    printf("Press Ctrl+C now to terminate.\n");
    fflush(stdout);

    while (1) {
        pause();
    }

    return 0;
}
