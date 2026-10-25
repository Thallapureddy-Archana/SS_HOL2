#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

int main() {
    key_t key;
    int msgid;
    key = ftok(".", 'A');
    printf("Generated key: 0x%x\n", key);
    
    msgid = msgget(key, IPC_CREAT | 0666);
    printf("Message queue ID: %d\n", msgid);
    printf("Key: 0x%x\n", key);
    
    int msgid_private = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    printf("\nCheck with: ipcs -q\n");
    printf("Remove with: ipcrm -q %d\n", msgid);
    
    return 0;
}
