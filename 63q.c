#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        pid_t parent_pid = getppid();

        printf("Child process started. PID = %ld\n", (long)getpid());
        printf("Parent PID = %ld\n", (long)parent_pid);
        fflush(stdout);

        sleep(2);

        kill(parent_pid, SIGKILL);
        printf("SIGKILL sent to parent.\n");
        fflush(stdout);
        sleep(2);
        printf("Child is still running.\n");
        printf("New parent PID = %ld\n", (long)getppid());

    } else {
        printf("Parent process started. PID = %ld\n", (long)getpid());
        printf("Waiting for the child to terminate me...\n");
        fflush(stdout);

        while (1) {
            pause();
        }
    }

    return 0;
}
