#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	while(1){
		write(STDOUT_FILENO,"P1: ",4);
		mkfifo("namedpipe_1",0777);
		int fd1 = open("namedpipe_1",O_WRONLY);
		int buf1[100];
		int bytes_read = read(STDIN_FILENO,buf1,sizeof(buf1));
		write(fd1,buf1,bytes_read);
		close(fd1);

		int fd2 = open("namedpipe_2",O_RDONLY);
		int buf2[100];
		int bytes_read1 = read(fd2,buf2,sizeof(buf2));
		write(STDOUT_FILENO,"P2: ",4);
		write(STDOUT_FILENO,buf2,bytes_read1);
		close(fd2);
	}
	return 0;
}
	
