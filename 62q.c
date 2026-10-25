
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    isigaction(SIGINT, &sa, NULL);

    printf("SIGINT is ignored for 10 seconds.\n");
    printf("Press Ctrl+C during this time.\n");
    sleep(10);

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    printf("Default SIGINT action restored.\n");
    printf("Press Ctrl+C now to terminate.\n");
    fflush(stdout);

    while (1) {
        pause();
    }

    return 0;
}
