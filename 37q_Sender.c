#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    const char message[] = "Hello from Sender!";
    mknod("pipe", S_IFIFO | 0666, 0);
    fd = open("pipe", O_WRONLY);
    write(fd, "Hello from Sender!", 18);
    write(1, "Message sent successfully\n", 26);
    close(fd);
    return 0;
}
