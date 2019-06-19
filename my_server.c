#include "my_server.h"

char * eg = "easter_egg";

char * answers[11] = {"entendido\n", "#0854780*\n", "nokia\n", "cabeza de calabaza\n", "easter_egg\n", ".runme\n", "indeterminado\n", "this is awesome\n", "cachiporra\n", "gdb rules\n", "/lib/x86_64-linux-gnu/ld-2.19.so\n"};

void (*funcs[11])(void) = {do_nothing, do_nothing, do_nothing, ebadf, do_nothing, do_nothing, mix_fds, do_nothing, quine, gdbme, do_nothing};

char * preguntas[11] = {
    "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
    "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?",
    "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? \n\
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
    "Bienvenidos al TP4 y felicitaciones, ya resolvieron el primer acertijo.\n\
    En este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel. \n\
    Además tendrán que investigar otras preguntas para responder durante la defensa. \n\
    El desafío final consiste en crear un servidor que se comporte igual que yo, además del cliente para comunicarse con el mismo. \n\
    \n\
    Deberán estar atentos a los desafios ocultos. \n\
    \n\
    Para verificar que sus respuestas tienen el formato correcto respondan a este desafío con 'entendido\\n'\n",
     "# \\033\[D \\033\[A \\033\[A \\033\[D \\033\[B \\033\[C \\033\[B \\033\[D *",
     "https://vocaroo.com/i/s19015zmR4t8",
     "EBADF... abrilo y verás",
     "respuesta = strings[43]", 
     ".debug_line .debug_str ? .symtab .strtab .shstrtab",
     "mixed fds",
     "Tango Hotel India Sierra India Sierra Alfa Whiskey Echo Sierra Oscar Mike Echo",
     "quine",
      "b gbdme y encontrará el valor mágico\n\
      try again",
      "/lib/x86_64-linux-gnu/libc-2.19.s0 ?"
};


int main(){
    int sock=0, clientfd = 0;

    struct sockaddr_in servaddr, client;

    create_connection(&sock, servaddr);

    listen_connection(sock, &clientfd, &client);

    run_challenges(clientfd, sock);

    close(sock);
}

void run_challenges(int clientfd, int sock){
    char buffer[MAX_BUFFER_SIZE];
    int aux=0;
    for(int i = 0; i < N_OF_CHALLENGES; i++){
        sleep(1);
        do_challenge(i);
        do{
            memset(buffer, 0, sizeof(buffer));
           
            if(!read(clientfd, buffer, sizeof(buffer)) ){
                close(sock);
                exit(EXIT_SUCCESS);
            }
            aux = strcmp(buffer, answers[i]);
            if(aux != 0) printf("Respuesta incorrecta %s \n", buffer);
        }while(aux != 0);
        printf("Respuesta correcta\n");
        sleep(1);
        //system("clear");
    }

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
    printf("%s\n\n", desafios[idx]);
    funcs[idx]();
    printf("--- PREGUNTA PARA INVESTIGAR ----\n\n");
    printf("%s\n", preguntas[idx]);
}

void do_nothing(){}

void ebadf(){
    char * string = "la respuesta para este acertijo es cabeza de calabaza";
    int fd = 5;
    write(fd, string, strlen(string));
}

void gdbme(){
    int var = 4;
    var = 0;
    if(var == 0x12345){
        printf("La respuesta es: %s", answers[9]);
    }else{
        printf("try again\n");
    }
}

void mix_fds(){
    char * string = "qwehqwhq hdwuidhodhakjc xnbcxmnvbidpio qpiowuanbc zchkhagdqw";
    char * correcto = "la respuesta es indeterminado";
    char c = 0;
    int turn = 0;
    srand(time(NULL));
    //reroute stderr and remove buffering from stdout
    dup2(STDERR_FILENO, STDOUT_FILENO);
    setvbuf(stdout, NULL, _IONBF, 0);
    while(*string || *correcto){
        turn = (int)(rand() %10) + 1;
        if(*string && turn > 4){
            fprintf(stderr, "%c", *string);
            string++;
        }else if(*correcto){
            fprintf(stdout, "%c", *correcto);
            correcto++;
        }
    }
    printf("\n\n");
    //restore stderr and restore line buffering in stdout
    dup2(STDERR_FILENO, 1);
    setvbuf(stdout, NULL, _IOLBF, 0);
}

void quine(){
    //1er buscar el archivo quine.c
    int gcc_val = 0;
    if(system("test -f quine.c") != 0){
        printf("File not found\n");
        return;
    }
    //compilar
    gcc_val = system("gcc quine.c -o quine");
    if(gcc_val != 0){
        perror("GCC returned:");
        return;
    }
    //correr y redirigir el output
    if(system("./quine > quineout.txt") != 0){
        perror("Error running quine");
        return;
    }
    //verificar output del quine con su propio .c
    if(system("diff quineout.txt quine.c") != 0){
        perror("not the same");
        return;
    }
    system("rm quineout.txt");
    system("rm quine");
    printf("La respuesta es: %s \n", answers[8]);
    return;
}
