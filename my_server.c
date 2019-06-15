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
    "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?"
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
     "EBADF... abrilo y verás"
};


int main(){
    char buffer[1024];
    int sock=0, clientfd = 0, aux =0;

    struct sockaddr_in servaddr, client;

    create_connection(&sock, servaddr);

    listen_connection(sock, &clientfd, &client);
    create_challenge();
    for(int i = 0; i < N_OF_CHALLENGES; i++){
        do_challenge(i);
        while(!strncmp(buffer, challenges[i].ch_ans, sizeof(challenges[i].ch_ans))
                || !aux){
            memset(buffer, 0, sizeof(buffer));
            read(clientfd, buffer, sizeof(buffer));
            aux = 1;
            if(!buffer[0]) printf("Respuesta incorrecta: %s \n", buffer);
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
    printf("------------ DESAFIO -----------\n");
    printf("%s\n", challenges[idx].ch_str);
    challenges[idx].ch_fun();
    printf("--- PREGUNTA PARA INVESTIGAR ----\n");
    printf("%s\n", challenges[idx].q_str);
}

void create_challenge(){
    for (int i = 0; i < N_OF_CHALLENGES; i++) {
        challenges[i].ch_ans = answers[i];
        challenges[i].ch_fun = funcs[i];
        challenges[i].ch_str = desafios[i];
        challenges[i].q_str = preguntas[i];
    }
}

void do_nothing(){}

void ebadf(){

}

void mix_fds(){

}


