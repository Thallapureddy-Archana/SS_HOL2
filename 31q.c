#include <unistd.h>
int main(){
    int fd[2];
    char buff[15];
    write(fd[1], "i am a pipe\n", 12);
    read(fd[0], buff, 12);
    write(1, buff, 12);
    close(fd[0]);
    close(fd[1]);
    return 0;
}