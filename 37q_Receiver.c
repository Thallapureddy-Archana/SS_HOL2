#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("myfifo", O_RDONLY);
    char buff[100];
    int n = read(fd, buff, sizeof(buff));
    if (n > 0) {
        write(1, buff, n);
        write(1, "\n", 1);
    }
    close(fd);
    return 0;
}
