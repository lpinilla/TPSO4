CC= gcc
OBJ= my_server.o client.o
GCCFLAGS= -Werror -g -std=c99
DEPS = my_server.h client.h

all: $(OBJ)
	objcopy --add-section .runme=runme --set-section-flags .runme=noload,readonly my_server.so


$(OBJ): $(DEPS) $(OBJ:.o=.c)
	$(CC) $(GCCFLAGS) -c $(@:.o=.c) -o $@
	$(CC) $(GCCFLAGS) $@ -o $(@:.o=.so)

clean:
	rm -r $(OBJ)
	rm -r $(OBJ:.o=.so)

.PHONY: all clean
