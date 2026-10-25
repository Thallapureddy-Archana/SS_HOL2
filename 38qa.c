#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(){
	while(1){
		int fd1 = open("namedpipe_1",O_RDONLY);
		char buf1[100];
		write(STDOUT_FILENO,"P1: ",4);
		int bytes_read1 = read(fd1,buf1,sizeof(buf1));
		write(STDOUT_FILENO,buf1,bytes_read1);
		close(fd1);

		mkfifo("namedpipe_2",0777);
		int fd2 = open("namedpipe_2",O_WRONLY);
		char buf2[100];
		write(STDOUT_FILENO,"P2: ",4);
		int bytes_read2 = read(STDIN_FILENO,buf2,sizeof(buf2));
		write(fd2,buf2,bytes_read2);
		close(fd2);
	}
	return 0;
}


