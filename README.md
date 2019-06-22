# Trabajo Práctico N°4 Sistemas Operativos

### Instrucciones de compilación y ejecución

Para compilar el programa

```bash
    make
```

Para ejecutar el programa en 2 terminales
En una terminal,

```bash
    ./my_server.so
```

En la otra

```bash
    ./client.so
```

O para correr en la misma

```bash
    ./my_server.so &
    ./client.so
```
En ambos casos, para cerrar el cliente, se debe escribir "cerrar". 

Para correr las respuestas automaticamente, hay que reescribir este comando, con el server corriendo.

```bash
    while read ans; do sleep 2; echo "$ans"; done < answers.txt | ./client.so
```

### Autores

- Lautaro Pinilla
- Micaela Banfi
- Joaquin Batilana
- Tomas Dorado
