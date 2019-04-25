/**
 * Charming Chatroom
 * CS 241 - Spring 2019
 */
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>




int main(int argc, char **argv) {
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	// If take this out whole thing breaks
	if (sock_fd == -1) {
		fprintf(stderr, "Socket error!");
	}
	
    /*QUESTION 2*/
	struct addrinfo hints, *result;
 
	/*QUESTION 3*/
    /*QUESTION 8*/	
	// for reusing port   
	int opt = 1;
	setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

  	/*QUESTION 4*/
	memset(&hints, 0, sizeof(hints));
    /*QUESTION 5*/
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;   
    /*QUESTION 6*/
	int s = getaddrinfo(NULL, "1234", &hints, &result);
	if (s != 0) {
		printf("return val: %d\n", s);
		fprintf(stderr, "yikes!\n");
		exit(1);
	}	

    /*QUESTION 9*/
	if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
		perror("bind()"); 
		exit(1);
	}

    /*QUESTION 10*/
	if (listen(sock_fd, 1) != 0) {
		perror("listen()");
		exit(1);
	}

	freeaddrinfo(result);

	int client_fd = accept(sock_fd, NULL, NULL);
	printf("Connection made: fd=%d\n", client_fd);


	char* buffer = calloc(1024, 1);
	while (1) {
		int bytes_read = read(client_fd, buffer, 1024);
		if (bytes_read == -1) {
			printf("error with read: %s\n", strerror(errno));
		}
		if (bytes_read == 0) {
			break;
		}
		//printf("bytes read: %d\n", bytes_read);
		printf("Received: %s\n", buffer);
		memset(buffer, 0, 1024);
	}

	free(buffer);
}
