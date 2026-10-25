
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    const char msg[] = "SIGFPE received!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGFPE, &sa, NULL);
    printf("Raising SIGFPE for demonstration.\n");
    fflush(stdout);

    raise(SIGFPE);

    printf("Signal handler returned.\n");
    return 0;
}
