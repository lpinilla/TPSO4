#include "server.h"

char * eg = "easter_egg";

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
    create_challenge_0();
    create_challenge_1();
    create_challenge_2();
    create_challenge_3();
    create_challenge_4();
}

void do_nothing(){}

void ebadf(){

}

void create_challenge_0(){
    challenges[0].ch_str = "Bienvenidos al TP4 y felicitaciones, ya resolvieron el primer acertijo. \
    En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel. \
    Además tendrán que investigar otras preguntas para responder durante la defensa. \
    El desafío final consiste en crear un servidor que se comporte igual que yo, además del cliente para comunicarse con el mismo. \
    \
    Deberán estar atentos a los desafios ocultos. \
    \
    Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con 'ente\
    ndido\n' ";
    challenges[0].ch_ans = "entendido\n";
    challenges[0].ch_fun = do_nothing;
    challenges[0].q_str = "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?";
}

void create_challenge_1(){
    challenges[1].ch_ans = "#0854780*";
    challenges[1].ch_fun = do_nothing;
    challenges[1].ch_str = "# \\033\[D \\033\[A \\033\[A \\033\[D \\033\[B \\033\[C \\033\[B \\033\[D *";
    challenges[1].q_str = "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?";
}

void create_challenge_2(){
    challenges[2].ch_ans = "nokia";
    challenges[2].ch_fun = do_nothing;
    challenges[2].ch_str = "https://vocaroo.com/i/s19015zmR4t8";
    challenges[2].q_str = "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? \
¿Por qué?";
}

void create_challenge_3(){
    challenges[3].ch_ans = "cabeza de calabaza";
    challenges[3].ch_str = "EBADF... abrilo y verás";
    challenges[3].q_str = "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?";
    challenges[3].ch_fun = ebadf;
}

void create_challenge_4(){
    challenges[4].ch_ans = "easter_egg";
    challenges[4].ch_str = "respuesta = strings[309]"; //TODO:revisar
    challenges[4].ch_fun = do_nothing;
    challenges[4].q_str = "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?";
}

