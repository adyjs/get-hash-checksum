CC = gcc
CFLAGS = -Wall -Werror -std=c99 -ggdb
# CFLAGS =  -std=c99 -ggdb
LDFLAGS = -lssl -lcrypto -lpthread -lncurses

SRCS =  file_io.c \
		get_hash_checksum.c \
		hash_compare.c \
		hash_config.c \
		hash_print.c \
		help.c \
		hex_char_parse.c \
		mutex.c \

# OBJS =  file_io.o \
# 		get_hash_checksum.o \
# 		hash_compare.o \
# 		hash_config.o \
# 		hash_print.o \
# 		help.o \
# 		hex_char_parse.o \
# 		mutex.o \

OBJS = $(patsubst %.c, %.o, $(SRCS))

hash: $(OBJS) main.c
	$(CC) $(OBJS) main.c -o $@ $(CFLAGS) $(LDFLAGS) && mv ./hash ../ && make clean

file_io.o: file_io.c
	$(CC) -c file_io.c

get_hash_checksum.o: get_hash_checksum.c
	$(CC) -c get_hash_checksum.c

hash_compare.o: hash_compare.c
	$(CC) -c hash_compare.c

hash_config.o: hash_config.c
	$(CC) -c hash_config.c

hash_print.o: hash_print.c
	$(CC) -c hash_print.c

help.o: help.c
	$(CC) -c help.c

hex_char_parse.o: hex_char_parse.c
	$(CC) -c hex_char_parse.c


.PHONY:clean

clean:
	rm *.o