/*
	Copyright 2019 Eliseu Silva Torres
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define MAX_NUM_PORT 65535

int
main(int argc, char **argv)
{
	struct sockaddr_in addr;
	int sfd, cfd;
	int port;
	char *host;
	
	if (argc < 2) {
		printf("IP address is missing!\n");
		exit(EXIT_FAILURE);
	}
	
	host = argv[1];
	printf("Port	Status\n");
	for (port = 1; port <= MAX_NUM_PORT; port++) {
		sfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sfd == -1) {
			printf("socket error\n");
			exit(EXIT_FAILURE);
		}
		
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(host);
		
		cfd = connect(sfd, (struct sockaddr *) &addr, sizeof addr);
		if (cfd == 0) 
			printf("%i	Open\n", port);				
		
		close(sfd);
		close(cfd);
	}
	
	exit(EXIT_SUCCESS);
} 
