
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>

volatile sig_atomic_t expired = 0;

void handler(int sig) {
    expired = 1;
}

int main() {
    struct itimerval timer = {0};
    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        write(2, "setitimer error\n", 16);
        return -1;
    }
    write(1, "SIGPROF Alaram Started 10s and 10ms\n", 32);

    while (!expired) {
        pause();
    }
    write(1, "SIGPROF received & timer expired.\n", 34);
    return 0;
}
