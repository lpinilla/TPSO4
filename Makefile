CC= gcc
OBJ= my_server.o client.o
GCCFLAGS= -Werror -g -std=c99
DEPS = server.h client.h

all: $(OBJ)

$(OBJ): $(DEPS) $(OBJ:.o=.c)
	$(CC) $(GCCFLAGS) -c $(@:.o=.c) -o $@
	$(CC) $(GCCFLAGS) $@ -o $(@:.o= )


clean:
	rm -r $(OBJ)
	rm -r $(OBJ:.o= )

.PHONY: all clean
