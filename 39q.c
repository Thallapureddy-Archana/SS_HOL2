#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

int main() {
    const char *fifo_path = "/tmp/fifo_select";
    char buffer[256];
    
    mkfifo(fifo_path, 0666);
    
    int fd = open(fifo_path, O_RDONLY | O_NONBLOCK);

    printf("Waiting for data on FIFO (10 second timeout)...\n");
    
    fd_set readfds;
    struct timeval timeout;
    
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    
    int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);
    
    if (ret == -1) {
        perror("select failed");
    } else if (ret == 0) {
        printf("Timeout: No data received within 10 seconds\n");
    } else {
        if (FD_ISSET(fd, &readfds)) {
            int n = read(fd, buffer, sizeof(buffer));
            if (n > 0) {
                printf("Data received: %s\n", buffer);
            } else {
                printf("EOF received\n");
            }
        }
    }
    
    close(fd);
    unlink(fifo_path);
    return 0;
}
