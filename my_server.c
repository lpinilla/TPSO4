#include "server.h"

char * eg = "easter_egg";

char * answers[11] = {"entendido\n", "#8054780*\n", "nokia\n", "cabeza de calabaza\n", "easter_egg\n", ".runme\n", "indeterminado\n", "this is awesome\n", "cachiporra\n", "gdb rules\n", "/lib/x86_64-linux-gnu/ld-2.19.so\n"};

void (*funcs[11])(void) = {do_nothing, do_nothing, do_nothing, ebadf, do_nothing, do_nothing, mix_fds, do_nothing, do_nothing, do_nothing, do_nothing};

char * preguntas[11] = {
    "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
    "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?",
    "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? \
¿Por qué?",
    "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?",
    "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?",
    "Un servidor suele crear un nuevo proceso o thread para atender las conecciones entrantes. Que conviene mas?",
    "Como se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
    "Que aplicaciones se pueden utilizar para ver el tráfico por la red?",
    "Sockets es un mecanismo de IPC. Que es más eficiente entre sockets y pipes?",
    "Características del protocolo SCTP",
    "Que es un RFC?"


};


char * desafios[11] = {
    "Bienvenidos al TP4 y felicitaciones, ya resolvieron el primer acertijo. \
    En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel. \
    Además tendrán que investigar otras preguntas para responder durante la defensa. \
    El desafío final consiste en crear un servidor que se comporte igual que yo, además del cliente para comunicarse con el mismo. \
    \
    Deberán estar atentos a los desafios ocultos. \
    \
    Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con 'ente\
    ndido\n' ",
     "# \\033\[D \\033\[A \\033\[A \\033\[D \\033\[B \\033\[C \\033\[B \\033\[D *",
     "https://vocaroo.com/i/s19015zmR4t8",
     "EBADF... abrilo y verás",
     "respuesta = strings[224]",
     ".data .bss .comment ? .shstrtab .symtab .strtab",
     "mixed fds",
     "Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo",
     "quine \
     gcc: error: quine.c: No such file  directory \
     gcc: fatal error: no input files \
    compilation terminated",
      "b gbdme y encontrará el valor mágico \
      try again",
      "/lib/x86_64-linux-gnu/libc-2.19.s0 ?",
      

};


int main(){
    char buffer[1024];
    int sock=0, clientfd = 0, aux =0;

    struct sockaddr_in servaddr, client;

    create_connection(&sock, servaddr);

    listen_connection(sock, &clientfd, &client);
    for(int i = 0; i < N_OF_CHALLENGES; i++){
        do_challenge(i);
        while(!strncmp(buffer, answers[i], sizeof(answers[i])) || !aux){
            memset(buffer, 0, sizeof(buffer));
            read(clientfd, buffer, sizeof(buffer));
            aux = 1;
            if(!buffer[0]) printf("Respuesta incorrecta: %s\n", buffer);
        }
        printf("Respuesta correcta\n");
        sleep(1);
        system("clear");
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

void do_challenge(int idx){
    printf("------------ DESAFIO -----------\n\n");
    printf("%s\n", desafios[idx]);
    funcs[idx]();
    printf("--- PREGUNTA PARA INVESTIGAR ----\n\n");
    printf("%s\n", preguntas[idx]);
}

void do_nothing(){}

void ebadf(){

}

void mix_fds(){

}


