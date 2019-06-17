#include "client.h"

int main(void){
	char buff[1024], c = 0;
	int char_read = 0;
	int sock;
	struct sockaddr_in servaddr;

	//creation of socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock < 0){
		perror("Error creating the socket\n");
		exit(EXIT_FAILURE);
	}
	memset(&servaddr, 0, sizeof(servaddr));

	///assign IP_ADRESS, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(URL);
	servaddr.sin_port = htons(PORT);

	//connect client socket to server socket
	if( connect(sock, (struct sockaddr *)&servaddr,sizeof(servaddr)) ){
		perror("Connection failed\n");
		exit(EXIT_FAILURE);
	}
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

	//Para poder ir probando respuestas
	/*while(1){
		c = getchar();
		buff[char_read++] = c;
		if(c == '\n'){
			//buff[char_read] = c;
			//printf("%s", buff);
			write(sock, buff, sizeof(buff));
			char_read = 0;
			memset(buff, 0, sizeof(buff));
		}
	}*/

	close(sock);
}
