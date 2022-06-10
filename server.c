#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


#define PORT 1234
#define BUFF_SIZE 4096
#define QUEUE_SIZE 10

int main(){
	int bytes;
	char buffer[BUFF_SIZE];
	printf("Server start\n");
	daemon(1, 1);
	int socket = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	socklen_t addresslen = sizeof address;
	Bind(socket, (struct sockaddr *) &address, addresslen);
	Listen(socket, QUEUE_SIZE);
	
	while(1){
		int sa = Accept(socket, (struct sockaddr *) &address, &addresslen);
		int fp = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fp < 0) printf("Output file error\n");
		while(1){
			bytes = read(sa, buffer, BUFF_SIZE);
			if(bytes <= 0) break;
			write(fp, buffer, bytes);
		}
		printf("File has been received, file output.txt was created or changed\n");
		close(fp);
		close(sa);
	}
	close(socket);
	return 0;
}
