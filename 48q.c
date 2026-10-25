#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(){
    int binary_semid, counting_semid;
    union semun arg;

    binary_semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    arg.val = 1;
    semctl(binary_semid, 0, SETVAL, arg);
    printf("Binary semaphore ID with Initial value 1 is : %d\n", binary_semid);
    
    counting_semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    arg.val = 5;
    semctl(counting_semid, 0, SETVAL, arg);
    printf("Counting semaphore ID with Initial value 5 is : %d\n", counting_semid);

    semctl(binary_semid, 0, IPC_RMID);
    semctl(counting_semid, 0, IPC_RMID);
    printf("\nBoth semaphore sets removed.\n");

    return 0;
}
