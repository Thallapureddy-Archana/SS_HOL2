#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

volatile sig_atomic_t timer_fired = 0;

void handler(int sig) {
    const char msg[] = "\nSIGVTALRM received (user CPU time timer)!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
    timer_fired = 1;
}

int main() {
    struct itimerval timer;
    volatile unsigned long counter = 0;

    signal(SIGVTALRM, handler);
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0; 
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);

    printf("ITIMER_VIRTUAL set for 2 seconds of user CPU time...\n");
    fflush(stdout);

    while (!timer_fired)
        counter++;

    printf("Busy-loop counter: %lu\n", counter);
    return 0;
}
