#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <message_queue_id>\n", argv[0]);
        printf("Get ID from Exercise 41 or ipcs -q\n");
        exit(1);
    }
    
    int msgid = atoi(argv[1]);
    struct msqid_ds buf;
    
    msgctl(msgid, IPC_STAT, &buf);
    printf("Message Queue Information (ID: %d):\n", msgid);
    printf("========================================\n");
    printf("a. Access permissions: %o\n", buf.msg_perm.mode & 0777);
    printf("b. Owner UID: %d, GID: %d\n", buf.msg_perm.uid, buf.msg_perm.gid);
    printf("   Creator UID: %d, GID: %d\n", buf.msg_perm.cuid, buf.msg_perm.cgid);
    printf("c. Last msgsnd time: %s", ctime(&buf.msg_stime));
    printf("   Last msgrcv time: %s", ctime(&buf.msg_rtime));
    printf("d. Last change time: %s", ctime(&buf.msg_ctime));
    printf("e. Current queue size: %lu bytes\n", buf.msg_cbytes);
    printf("f. Number of messages: %lu\n", buf.msg_qnum);
    printf("g. Max queue size: %lu bytes\n", buf.msg_qbytes);    
    printf("h. Last sender PID: %d\n", buf.msg_lspid);
    printf("   Last receiver PID: %d\n", buf.msg_lrpid);
    
    return 0;
}
