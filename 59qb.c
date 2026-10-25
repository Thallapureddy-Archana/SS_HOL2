#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    const char msg[] = "\nSIGINT caught! Press Ctrl+C again to test.\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGINT, handler);
    printf("Press Ctrl+C to generate SIGINT. Press Ctrl+\\ to quit.\n");
    fflush(stdout);

    while (1)
        pause();

    return 0;
}
