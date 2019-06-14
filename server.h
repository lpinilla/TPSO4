#ifndef _SERVER_H_
#define _SERVER_H_

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <string.h>

#define PORT 23423 
#define URL "127.0.0.1"

void create_connection(int * sock, struct sockaddr_in servaddr);
void listen_connection(int sock, int * clientfd, struct sockaddr_in * client);


#endif