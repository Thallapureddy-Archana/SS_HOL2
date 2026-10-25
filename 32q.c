#include<unistd.h>
#include <sys/wait.h>
int main(){
    int fd[2];
    char buff[20];
    
    pipe(fd);

    if(fork() < 0){
        write(2, "fork error\n", 11);
        close(fd[0]);
        close(fd[1]);
        return -1;
    }
    if(fork() > 0){
        write(1, "parent running\n", 15);
        close(fd[0]);
        sleep(5);
        write(fd[1], "hello child\n", 12);
        close(fd[1]);
    }
    else{
        write(1, "child running\n", 14);
        close(fd[1]);
        int n = read(fd[0], buff, 20);
        write(1, buff, n);
        close(fd[0]);
    }
    return 0;
}