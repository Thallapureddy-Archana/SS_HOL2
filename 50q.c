#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void wait_sem(int semid, int semnum)
{
    struct sembuf op = {semnum, -1, 0};

    if (semop(semid, &op, 1) == -1) {
        perror("semop wait");
        exit(1);
    }
}

void signal_sem(int semid, int semnum)
{
    struct sembuf op = {semnum, 1, 0};

    if (semop(semid, &op, 1) == -1) {
        perror("semop signal");
        exit(1);
    }
}

int main()
{
    int semid;
    union semun arg;
    pid_t pid;

    setbuf(stdout, NULL);

    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    arg.val = 1;

    if (semctl(semid, 0, SETVAL, arg) == -1 ||
        semctl(semid, 1, SETVAL, arg) == -1) {
        perror("semctl");
        semctl(semid, 0, IPC_RMID);
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        semctl(semid, 0, IPC_RMID);
        exit(1);
    }

    if (pid == 0) {
        printf("Child: waiting for semaphore 1\n");
        wait_sem(semid, 1);

        printf("Child: acquired semaphore 1\n");
        sleep(2);

        printf("Child: waiting for semaphore 0\n");
        wait_sem(semid, 0);  
	    printf("Child: acquired semaphore 0\n");

        signal_sem(semid, 0);
        signal_sem(semid, 1);
        exit(0);
    }
    else {
        printf("Parent: waiting for semaphore 0\n");
        wait_sem(semid, 0);

        printf("Parent: acquired semaphore 0\n");
        sleep(2);

        printf("Parent: waiting for semaphore 1\n");
        wait_sem(semid, 1); 
        printf("Parent: acquired semaphore 1\n");

        signal_sem(semid, 1);
        signal_sem(semid, 0);
        wait(NULL);
    }
    semctl(semid, 0, IPC_RMID);
    return 0;
}
