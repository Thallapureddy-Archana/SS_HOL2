#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

void handler(int sig) {
    const char msg[] = "SIGALRM received from ITIMER_REAL!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    struct sigaction_dummy { int unused; }; 
    struct itimerval timer;

    signal(SIGALRM, handler);
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; 
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    printf("ITIMER_REAL set for 3 seconds...\n");
    fflush(stdout);

    while (1)
        pause();

    return 0;
}
