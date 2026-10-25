
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void) {
    struct rlimit rlim;

    if (getrlimit(RLIMIT_NOFILE, &rlim) == 0) {
        printf("File descriptor limits:\n");

        if (rlim.rlim_cur == RLIM_INFINITY)
            printf("  Soft limit: Unlimited\n");
        else
            printf("  Soft limit: %llu\n",
                   (unsigned long long)rlim.rlim_cur);

        if (rlim.rlim_max == RLIM_INFINITY)
            printf("  Hard limit: Unlimited\n");
        else
            printf("  Hard limit: %llu\n",
                   (unsigned long long)rlim.rlim_max);
    } else {
        perror("getrlimit");
    }

#ifdef OPEN_MAX
    printf("\nOPEN_MAX (compile-time): %d\n", OPEN_MAX);
#else
    printf("\nOPEN_MAX is not defined at compile time.\n");
#endif

    printf("\nTesting maximum additional open files...\n");

    int *fds = NULL;
    size_t count = 0;
    size_t capacity = 0;
    int fd;

    while ((fd = open("/dev/null", O_RDONLY)) != -1) {
        if (count == capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            int *temp = realloc(fds, new_capacity * sizeof(*fds));

            if (temp == NULL) {
                perror("realloc");
                close(fd);
                break;
            }

            fds = temp;
            capacity = new_capacity;
        }

        fds[count++] = fd;

        if (count % 100 == 0)
            printf("  Opened %zu files...\n", count);
    }

    if (fd == -1) {
        int saved_errno = errno;
        printf("Maximum additional files opened: %zu\n", count);
        printf("Open error: %s\n", strerror(saved_errno));
    }

    /* Close the actual descriptors returned by open() */
    for (size_t i = 0; i < count; i++) {
        if (close(fds[i]) == -1)
            perror("close");
    }

    free(fds);

    printf("\nPipe buffer size:\n");

    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    int pipe_size = fcntl(pipefd[0], F_GETPIPE_SZ);

    if (pipe_size != -1)
        printf("  Pipe size: %d bytes\n", pipe_size);
    else
        perror("fcntl F_GETPIPE_SZ");

    int flags = fcntl(pipefd[1], F_GETFL);

    if (flags == -1 ||
        fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl non-blocking mode");
    } else {
        char buf[4096] = {0};
        size_t written = 0;

        while (1) {
            ssize_t n = write(pipefd[1], buf, sizeof(buf));

            if (n > 0) {
                written += (size_t)n;
            } else if (n == -1 && errno == EINTR) {
                continue;
            } else if (n == -1 &&
                       (errno == EAGAIN || errno == EWOULDBLOCK)) {
                break;
            } else {
                if (n == -1)
                    perror("write");
                break;
            }
        }

        printf("  Measured pipe capacity: %zu bytes\n", written);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    printf("  PIPE_BUF (atomic write guarantee): %d bytes\n",
           PIPE_BUF);

    return 0;
}
