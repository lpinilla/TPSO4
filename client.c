#include "client.h"

int main(int argc, char * argv[]){
	int sock;
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));

    set_everything(&sock,servaddr);
    check_answers(sock);

    close(sock);
}


void set_everything(int * sock, struct sockaddr_in servaddr){
	socket_creation(sock,servaddr);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(URL);
	servaddr.sin_port = htons(PORT);
	connect_sockets(sock,servaddr);
	printf("Para cerrar el cliente, escriba \"cerrar\"\n");
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


void check_answers(int sock){
	//Para poder ir probando respuestas
	char c=0;
	char buff[BUFF_SIZE];
	int char_read = 0,end=0;
    memset(buff, 0, BUFF_SIZE * sizeof(char));

	while(end!=1){
		c = getchar();
		buff[char_read++] = c;

		if(c == '\n'){
			write(sock, buff, sizeof(buff));
			char_read = 0;
			memset(buff, 0, sizeof(buff));
		}
		else if(strncmp(buff,"cerrar",6)==0){
			end=1;
		}
	}
}
