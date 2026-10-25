#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    pid_t pid;
    pipe(pipefd);
    pid = fork();

    if (pid == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        // close(1);
        // dup(pipefd[1]);
        // fcntl(pipefd, 1);
        close(pipefd[1]);
        execlp("ls", "ls", "-l", NULL);
        write(2, "exec failed\n", 12);
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        // close(0);
        // dup(pipefd[0]);
        // fcntl(pipefd, 0);
        close(pipefd[0]);
        execlp("wc", "wc", NULL);
        write(2, "exec failed\n", 12);
    }

    return 0;
}