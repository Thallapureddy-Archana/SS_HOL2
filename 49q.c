#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    int semid, fd, ticket;
    struct sembuf op;
    union semun arg;
    char buffer[32];
    ssize_t n;

    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    fd = open("ticket.txt", O_RDWR | O_CREAT, 0666);

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = SEM_UNDO;
    semop(semid, &op, 1);
    printf("Semaphore acquired.\n");

    lseek(fd, 0, SEEK_END);

    if (lseek(fd, 0, SEEK_CUR) == 0) {
        if (write(fd, "100", 3) != 3) {
            perror("initialize ticket");
            goto error;
        }
    }
    lseek(fd, 0, SEEK_SET);

    n = read(fd, buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';
    ticket = atoi(buffer);
    ticket++;
    snprintf(buffer, sizeof(buffer), "%d", ticket);

    if (lseek(fd, 0, SEEK_SET) == -1 ||
        ftruncate(fd, 0) == -1 ||
        write(fd, buffer, strlen(buffer)) != (ssize_t)strlen(buffer)) {
        perror("update ticket");
        goto error;
    }
    printf("New ticket number: %d\n", ticket);
    op.sem_op = 1;
    semop(semid, &op, 1);
    printf("Semaphore released.\n");
    close(fd);
    semctl(semid, 0, IPC_RMID);
    printf("Semaphore removed.\n");
    return 0;
error:
    op.sem_op = 1;
    semop(semid, &op, 1);
    close(fd);
    semctl(semid, 0, IPC_RMID);
    exit(1);
}
