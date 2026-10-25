#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    char path[50];
    char buffer[4096];
    int n;
    
    if(argc != 2)
    {
        write(2, "No PID Found\n", 13);
        return -1;
    }
    
    
    int i = 0;
    int j = 0;
    
    char prefix[] = "/proc/";
    while(prefix[j] != '\0')
    {
        path[i++] = prefix[j++];
    }
    
    j = 0;
    
    while(argv[1][j] != '\0')
    {
        path[i++] = argv[1][j++];
    }
    
    j = 0;
    
    char suffix[] = "/stat";
    while(suffix[j] != '\0')
    {
        path[i++] = suffix[j++];
    }

    path[i] = '\0';

    fd = open(path, O_RDONLY);

    if(fd == -1)
    {
        write(2, "Open error\n", 11);
        return -1;
    }

    n = read(fd, buffer, sizeof(buffer));

    if(n == -1)
    {
        write(2, "Read error\n", 11);
        close(fd);
        return -1;
    }

    write(1, buffer, n);

    close(fd);

    return 0;
}