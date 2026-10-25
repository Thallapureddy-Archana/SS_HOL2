#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) {
    const char msg[] = "SIGFPE caught!\n";
    write(STDOUT_FILENO, msg, sizeof(msg) - 1);
}

int main() {
    signal(SIGFPE, handler);

    printf("Raising SIGFPE for demonstration...\n");
    fflush(stdout);
    raise(SIGFPE);

    printf("Returned from SIGFPE handler.\n");
    return 0;
}
