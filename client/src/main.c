#include <stdio.h>

// void printf_nl(const char *);

// int main(void) { printf_nl("Hello, World!"); }

// void printf_nl(const char *idk) { printf("%s\n", idk); }

#include "constants.h"
#include "err_handler.h"
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

void func(FILE *sockfd) {
    // struct pollfd p = {.fd = fileno(sockfd), .events = POLLIN};
    // char buff[MAX];
    char *tmp_u;
    // int n;
    for (;;) {
        printf(
            "Please enter a product to search, and press \"Enter\" afterward:\n"
        );
        scanf("%ms", &tmp_u);

        if (tmp_u != NULL) {
            fputs(tmp_u, sockfd);
            fputc('\n', sockfd);
        }

        fflush(sockfd);

        logger(tmp_u);

        free(tmp_u);
        // tmp_u = NULL;

        // poll(&p, 1, 30);
        // printf("{.events = %d, .revents = %d}\n", p.events, p.revents);

        // if (p.revents & POLLIN) {
        // rewind(sockfd);
        fscanf(sockfd, "%ms", &tmp_u);
        if (tmp_u != NULL) {
            printf("%s\n", tmp_u);
            logger(tmp_u);
            free(tmp_u);
        } else {
            logger("Server Disconnected");
            break;
        }
        // }
    }
}

int main() {
    int sockfd;
    sockaddr_in servaddr;

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
    servaddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    servaddr.sin_port = htons(SERVER_PORT);

    // connect the client socket to server socket
    validate_or_die(
        connect(sockfd, (sockaddr *)&servaddr, sizeof(servaddr)) == 0,
        "Connection Failed, Server is not online."
    );

    printf("Connected to server..\n");

    // function for chat
    FILE *s = fdopen(sockfd, "r+");
    func(s);

    // close the socket
    fclose(s);
}
