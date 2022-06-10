#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 1234
#define BUFF_SIZE 4096

int main(int argc, char* argv[]){
	// Args check
	if(argc != 2){
		printf("Type: ./client filename.txt\n");
		exit(EXIT_FAILURE);
	}
	
	// Open file
	int fp = open(argv[1], O_RDONLY);
	if(fp == -1){
		printf("File not found\n");
		exit(EXIT_FAILURE);
	}
	
	// Start client
	printf("Client start\n");
	int socket = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	Inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
	Connect(socket, (struct sockaddr *) &address, sizeof address);
	
	// File transfer
	int bytes;
	char buffer[BUFF_SIZE];
	while(1){
		bytes = read(fp, buffer, BUFF_SIZE);
		if(bytes <= 0) break;
		write(socket, buffer, bytes);
	}
	printf("File has been transferred\n");

	close(fp);
	close(socket);
	return 0;
}
