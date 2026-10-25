
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void *handle_client(void *arg)
{
    int connfd = (int)(intptr_t)arg;
    char buffer[1024];
    ssize_t n;

    n = recv(connfd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';

        printf("Thread %lu received: %s\n",
               (unsigned long)pthread_self(), buffer);

        char reply[] = "Message received by server";
        send(connfd, reply, strlen(reply), 0);
    }

    close(connfd);
    return NULL;
}

int main()
{
    int sockfd, connfd;
    int opt = 1;
    struct sockaddr_in server;
    pthread_t tid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
               &opt, sizeof(opt));

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *)&server,
             sizeof(server)) == -1) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 5) == -1) {
        perror("listen");
        close(sockfd);
        exit(1);
    }

    printf("Pthread server listening on port 8080...\n");

    while (1) {
        connfd = accept(sockfd, NULL, NULL);

        if (connfd == -1) {
            if (errno == EINTR)
                continue;
            perror("accept");
            continue;
        }

        if (pthread_create(&tid, NULL, handle_client,
                           (void *)(intptr_t)connfd) != 0) {
            fprintf(stderr, "pthread_create failed\n");
            close(connfd);
            continue;
        }

        pthread_detach(tid);
    }

    close(sockfd);
    return 0;
}

