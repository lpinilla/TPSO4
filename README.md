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
Para correr las respuestas automaticamente, hay que reescribir este comando, con el server corriendo.
```bash
    while read ans; do echo "$ans"; sleep 2; done < answers.txt | ./client.so
```

### Autores
- Lautaro Pinilla
- Micaela Banfi 
- Joaquin Batilana 
- Tomas Dorado 
