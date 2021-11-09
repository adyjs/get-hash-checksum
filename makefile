CC = gcc
# CFLAGS = -Wall -Werror -std=c99 -ggdb
CFLAGS =  -std=c99 -ggdb
LDFLAGS = -lssl -lcrypto -lpthread -lncurses
LIBS = libget-hash.o

all:	libget-hash.o	get-hash

get-hash:	get-hash.c libget-hash.o
	${CC} -o $@ $< ${LIBS} ${CFLAGS} ${LDFLAGS}


libget-hash.o:	libget-hash.c
	${CC} -c libget-hash.c


.PHONY:clean

clean:
	rm get-hash libget-hash.o