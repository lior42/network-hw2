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
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void func(int sockfd) {
    char buffer[4096] = {0};
    for (;;) {
        printf("\n");
        printf(
            "\nEnter a term to search (Enter \"quit\" to end converstation):\n"
        );
        fgets(buffer, 4096, stdin);
        // Remove \n at the end.
        buffer[strlen(buffer) - 1] = 0;
        if (strcmp(buffer, "quit") == 0)
            break;
        write(sockfd, buffer, 4096);
        fsync(sockfd);
        read(sockfd, buffer, 4096);
        fsync(sockfd);
        printf("\nServer answer:\t%s", buffer);
    }
    strcpy(buffer, SERVER_END_COMMUNICATION);
    write(sockfd, buffer, 4096);

    printf("\nBye Bye!\n");
}

int main(void) {
    int sockfd;
    sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(0);
    }

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
    func(sockfd);

    // close the socket
    close(sockfd);
}
