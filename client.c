#include "client.h"

int main(int argc, char * argv[]){
	int sock;
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

	//printf("argc: %d , argv: %s \n",argc,argv[1]);

	if(argc>2){
		perror("Argument error\n");
		exit(EXIT_FAILURE);
	}
	else if(argc==1){
		set_everything(&sock,servaddr);
		check_answers(sock);
	}
	else{
		if(strcmp(argv[1],"1")!=0 && strcmp(argv[1],"respuestas")!=0){
				perror("Argument error\n");
				exit(EXIT_FAILURE);
		}
		else{
			set_everything(&sock,servaddr);
		}
		if(strcmp(argv[1],"1")==0){ //run automatic answers
			run_answers(sock);
		}
		else if(strcmp(argv[1],"respuestas")==0){ //complete answers
			check_answers(sock);
		}
		
	}

    close(sock);
}


void set_everything(int * sock, struct sockaddr_in servaddr){
	socket_creation(sock,servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(URL);
	servaddr.sin_port = htons(PORT);
	connect_sockets(sock,servaddr);
}

void socket_creation(int * sock,struct sockaddr_in servaddr){
	*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(*sock < 0){
		perror("Error creating the socket\n");
		exit(EXIT_FAILURE);
	}		
}


void connect_sockets(int * sock, struct sockaddr_in servaddr){
	if( connect(*sock, (struct sockaddr *)&servaddr,sizeof(servaddr)) ){
		perror("Connection failed\n");
		exit(EXIT_FAILURE);
	}
}

void run_answers(int sock){
	//escribe las respuestas automaticamente
	sleep(2);
	write(sock, "entendido\n", strlen("entendido\n"));
    sleep(2);
    write(sock, "#0854780*\n", strlen("#0854780*\n"));
    sleep(2);
    write(sock, "nokia\n", strlen("nokia\n"));
    sleep(2);
    write(sock, "cabeza de calabaza\n", strlen("cabeza de calabaza\n"));
    sleep(2);
	write(sock, "easter_egg\n", strlen("easter_egg\n"));
	sleep(2);
	write(sock, ".runme\n", strlen(".runme\n"));
	sleep(2);
	write(sock, "indeterminado\n", strlen("indeterminado\n"));
	sleep(2);
	write(sock, "this is awesome\n", strlen("this is awesome\n"));
	sleep(2);
	write(sock, "cachiporra\n", strlen("cachiporra\n"));
	sleep(2);
	write(sock, "gdb rules\n", strlen("gdb rules\n"));
	sleep(2);
	write(sock, "/lib/x86_64-linux-gnu/ld-2.19.so\n", strlen("/lib/x86_64-linux-gnu/ld-2.19.so\n"));
	sleep(2);
}

void check_answers(int sock){
	//Para poder ir probando respuestas
	char c=0;
	char buff[BUFF_SIZE];
	int char_read = 0;
    memset(buff, 0, BUFF_SIZE * sizeof(char));

	while(1){
		c = getchar();
		buff[char_read++] = c;
		if(c == '\n'){
			write(sock, buff, sizeof(buff));
			char_read = 0;
			memset(buff, 0, sizeof(buff));
		}
	}
}