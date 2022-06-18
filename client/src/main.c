#include <stdio.h>

// void printf_nl(const char *);

// int main(void) { printf_nl("Hello, World!"); }

// void printf_nl(const char *idk) { printf("%s\n", idk); }

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include "logger.h"
#define MAX 80
#define PORT 8888
#define SA struct sockaddr
#define bzero(a, b) memset(a, EOF, b)


void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
void func(FILE * sockfd)
{
	// char buff[MAX];
	char * tmp_u = calloc(strlen("Food\n")+1, sizeof(char));
	// int n;
	for (;;) {
		// scanf("%ms",&tmp_u);
		strcpy(tmp_u, "Food\n");
		if(tmp_u != NULL)
		{
			fputs(tmp_u, sockfd);
		}
		fflush(sockfd);
		logger(tmp_u);
		free(tmp_u);
		delay(5);
		fscanf(sockfd, "%ms", &tmp_u);
		// logger(tmp_u);
		if(tmp_u != NULL)
		{
			printf("%s\n", tmp_u);
		}
		free(tmp_u);
		break;
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	FILE *s=fdopen(sockfd, "r+");
	func(s);

	// close the socket
	fclose(s);
}
