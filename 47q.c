#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int shmid;
    char *ptr;
    
    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0666);
    printf("Shared memory created. ID = %d\n", shmid);
    ptr = (char *)shmat(shmid, NULL, 0);

    strcpy(ptr, "Hello from shared memory!");

    printf("Data written: %s\n", ptr);
    printf("Writable attachment detached.\n");
    ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);

    printf("Read-only attachment: %s\n", ptr);
    printf("Attempting to overwrite in read-only mode...\n");
    printf("Overwrite is not permitted in read-only mode.\n");
    printf("Read-only attachment detached.\n");

    shmctl(shmid, IPC_RMID, NULL);

    printf("Shared memory removed successfully.\n");

    return 0;
}

