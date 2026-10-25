#include <unistd.h>
#include <sys/stat.h>

int main()
{
    mknod("fifo_syscall", S_IFIFO | 0666, 0);
    write(1, "FIFO created using mknod()\n", 27);
    
    mkfifo("fifo_library", 0666);
    write(1, "FIFO created using mkfifo()\n", 28);

    return 0;
}
