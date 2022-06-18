#include <stdio.h>

// void printf_nl(const char *);

// int main(void) { printf_nl("Hello, World!"); }

// void printf_nl(const char *idk) { printf("%s\n", idk); }

#include "logger.h"
#include "shared.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <time.h>

#include <poll.h>

#define MAX 80
#define PORT 8888
#define SA struct sockaddr

void func(FILE *sockfd) {
    struct pollfd p = {.fd = fileno(sockfd), .events = POLLIN};
    // char buff[MAX];
    char *tmp_u;
    // int n;
    for (;;) {
        scanf("%ms", &tmp_u);
        // strcpy(tmp_u, "Food\n");
        if (tmp_u != NULL) {
            fputs(tmp_u, sockfd);
            fputc('\n', sockfd);
        }
        fflush(sockfd);
        logger(tmp_u);
        free(tmp_u);
        tmp_u = NULL;

        poll(&p, 1, -1);
        printf("{.events = %d, .revents = %d}\n", p.events, p.revents);

        if (p.revents & POLLIN) {
            fscanf(sockfd, "%ms", &tmp_u);
            if (tmp_u != NULL) {
                printf("%s\n", tmp_u);
            }
            logger(tmp_u);
            free(tmp_u);
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    } else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    } else
        printf("connected to the server..\n");

    // function for chat
    FILE *s = fdopen(sockfd, "r+");
    func(s);

    // close the socket
    fclose(s);
}
