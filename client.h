#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <linux/rtc.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 23423 
#define URL "127.0.0.1"
#define BUFF_SIZE 1024

void socket_creation(int * sock,struct sockaddr_in servaddr);
void connect_sockets(int * sock,struct sockaddr_in servaddr);
void run_answers(int sock);
void check_answers(int sock);
void set_everything(int * sock, struct sockaddr_in servaddr);



#endif
