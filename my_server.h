#ifndef _SERVER_H_
#define _SERVER_H_

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


#define PORT 23423
#define URL "127.0.0.1"
#define N_OF_CHALLENGES 11
#define MAX_BUFFER_SIZE 1024

void create_connection(int * sock, struct sockaddr_in servaddr);
void listen_connection(int sock, int * clientfd, struct sockaddr_in * client);
void run_challenges(int clientfd, int sock);

void do_challenge(int idx);
//funcion para no hacer nada y esperar respuesta
void do_nothing();
//funcion que genera un ebadf con un string deseado
void ebadf();
//funcion que mezcla los file descriptors
void mix_fds();
//funcion para analizar con gdb
void gdbme();
//funcion que verifica la existencia y el correcto funcionamiento de quine
void quine();



#endif
