CC = gcc
CFLAGS = -Wall -Werror -std=c99 -ggdb
# CFLAGS =  -std=c99 -ggdb
LDFLAGS = -lssl -lcrypto -lpthread -lncurses
LIBS = libget-hash-checksum.o

all:libget-hash-checksum.o	get-hash-checksum

get-hash-checksum:	get-hash-checksum.c libget-hash-checksum.o
	${CC} -o $@ $< ${LIBS} ${CFLAGS} ${LDFLAGS}


libget-hash-checksum.o:	libget-hash-checksum.c
	${CC} -c libget-hash-checksum.c	


.PHONY:clean

clean:
	rm get-hash-checksum libget-hash-checksum.o