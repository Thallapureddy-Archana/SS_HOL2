#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
void handle_client(int connfd)
{
    char buffer[1024];
    ssize_t n;

    n = recv(connfd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Child %d received: %s\n", getpid(), buffer);

        char reply[] = "Message received by server";
        send(connfd, reply, strlen(reply), 0);
    }

    close(connfd);
    exit(0);
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    signal(SIGCHLD, SIG_IGN);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    int opt = 1;
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

    printf("Fork server listening on port 8080...\n");

    while (1) {
        connfd = accept(sockfd, NULL, NULL);

        if (connfd == -1) {
            if (errno == EINTR)
                continue;
            perror("accept");
            continue;
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            close(connfd);
            continue;
        }

        if (pid == 0) {
            close(sockfd);
            handle_client(connfd);
        } else {
            close(connfd);
        }
    }

    close(sockfd);
    return 0;
}
