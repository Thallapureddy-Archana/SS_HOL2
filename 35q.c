
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int p1[2], p2[2];
    pid_t pid1, pid2;

    if (pipe(p1) == -1 || pipe(p2) == -1)
    {
        write(2, "Pipe creation failed\n", 21);
        return 1;
    }

    pid1 = fork();

    if (pid1 == -1)
    {
        write(2, "Fork failed\n", 12);
        return 1;
    }

    if (pid1 == 0)
    {
        dup2(p1[1], 1);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("ls", "ls", "-l", (char *)NULL);

        write(2, "ls failed\n", 10);
        return -1;
    }

    pid2 = fork();

    if (pid2 == -1)
    {
        write(2, "Fork failed\n", 12);
        return 1;
    }

    if (pid2 == 0)
    {
        dup2(p1[0], 0);
        dup2(p2[1], 1);

        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);

        execlp("grep", "grep", "d", (char *)NULL);

        write(2, "grep failed\n", 12);
        return -1;
    }

    dup2(p2[0], 0);

    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    execlp("wc", "wc", (char *)NULL);

    write(2, "wc failed\n", 10);
    return 1;
}
