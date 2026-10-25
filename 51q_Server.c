#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int sockfd, connfd;
    struct sockaddr_in server, client;
    char buffer[1024];
    int opt = 1;
    socklen_t len = sizeof(client);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
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

    printf("Server waiting for client...\n");
    connfd = accept(sockfd, (struct sockaddr *)&client, &len);
    if (connfd == -1) {
        perror("accept");
        close(sockfd);
        exit(1);
    }

    printf("Client connected.\n");

    int n = recv(connfd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);
        char reply[] = "Hello from server!";
        send(connfd, reply, strlen(reply), 0);
    }

    close(connfd);
    close(sockfd);

    return 0;
}
