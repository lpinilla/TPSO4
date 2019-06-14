#include "server.h"

int main(){
    char buffer[1024];
    int sock, clientfd = 0;

    struct sockaddr_in servaddr, client;

    create_connection(&sock, servaddr);

    listen_connection(sock, &clientfd, &client);

    for(int i = 0; i < 11; i++){
        memset(buffer, 0, sizeof(buffer));
        read(clientfd, buffer, sizeof(buffer));
        printf("%s", buffer);
    }
    close(sock);
}

void create_connection(int * sock, struct sockaddr_in servaddr){
    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if(*sock < 0){
        perror("Error creating socket\n");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));

    //ASSIGN IP,PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if(bind(*sock, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0){
        perror("Bind failed\n");
        exit(EXIT_FAILURE);
    }
}

void listen_connection(int sock, int * clientfd, struct sockaddr_in * client){
    int len;
    if(listen(sock, 5) != 0){
        perror("Listening failed\n");
    }
    printf("Server is listening\n");
    len = sizeof(*client);

    *clientfd = accept(sock, (struct sockaddr*) client, &len);
    if(*clientfd < 0){
        perror("Confirmation failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Server accepted connection\n");
}
