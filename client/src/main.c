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
#include<sys/types.h>
#include<netinet/in.h>

void func(int sockfd) {
    char buffer[4096] = {0};
    while(strcmp(buffer, SERVER_END_COMMUNICATION) != 0) 
       {
         write(sockfd,buffer,4096);
         read(sockfd,buffer,4096);
         printf("\n");
         printf("\nServer message:\t%s",buffer);
         printf("\nType your message:\t");
         fgets(buffer,4096,stdin);
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
    func(sockfd);

    // close the socket
    close(sockfd);
}
