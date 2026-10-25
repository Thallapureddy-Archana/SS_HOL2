#include<unistd.h>
#include <sys/wait.h>
int main(){
    int p1[2], p2[2];
    char buff1[20];
    char buff2[20];

    if(pipe(p1) == -1 || pipe(p2) == -1){
        write(2, "pipe error\n", 11);
        return -1;
    }

    pid_t pid = fork();
    if(pid < 0){
        write(2, "fork error\n", 11);
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
        return -1;
    }

    if(pid > 0){
        close(p1[0]);
        close(p2[1]);

        write(p1[1], "hello child\n", 12);
        close(p1[1]);

        int n = read(p2[0], buff2, 20);
        write(1, "parent received : ", 18);
        write(1, buff2, n);
        close(p2[0]);
        wait(NULL);
    }
    else{
        close(p1[1]);
        close(p2[0]);
        
        int n = read(p1[0], buff1, 20);
        write(1, "child received : ", 17);
        write(1, buff1, n);
        close(p1[0]);

        write(p2[1], "hello parent\n", 13);
        close(p2[1]);
    }
    return 0;
}