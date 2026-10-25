#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    const char msg[] = "SIGALRM received from alarm()!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGALRM, handler);

    printf("Setting alarm for 5 seconds...\n");
    fflush(stdout);
    alarm(5);

    while (1)
        pause();

    return 0;
}
