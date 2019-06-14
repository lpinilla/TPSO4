SOURCES=my_server client
GCCFLAGS= -Werror -g -std=c99

all: $(SOURCES)

$(SOURCES):
	gcc $(GCCFLAGS) $@.c -o $@

clean:
	rm -r $(SOURCES)

.PHONY: all clean
