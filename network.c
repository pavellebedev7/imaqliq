#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol){
	int result = socket(domain, type, protocol);
	if(result == -1){
		printf("Socket error\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
	int result = bind(sockfd, addr, addrlen);
	if(result == -1){
		printf("Bind error\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int Listen(int sockfd, int backlog){
	int result = listen(sockfd, backlog);
	if(result == -1){
		printf("Listen error\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	int result = accept(sockfd, addr, addrlen);
	if(result == -1){
		printf("Accept error\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int Inet_pton(int af, const char *src, void *dst) {
    int result = inet_pton(af, src, dst);
    if (result == 0) {
        printf("Invalid network address\n");
        exit(EXIT_FAILURE);
    }
    if (result == -1) {
        printf("Invalid address family\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int result = connect(sockfd, addr, addrlen);
    if (result == -1) {
        printf("Connect error\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

