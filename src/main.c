#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
// #include <openssl/evp.h>
// #include <openssl/md2.h>
#include <openssl/md4.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
// #include <ncurses.h>

#include "../include/get_hash_checksum.h"
#include "../include/file_io.h"
#include "../include/hash_print.h"
#include "../include/hash_config.h"
#include "../include/hash_compare.h"
#include "../include/hex_char_parse.h"
#include "../include/mutex.h"
#include "../include/help.h"



int main(int argc, char *argv[]){
    // initscr();
    if(argc == 1 || argc > 3){
        help();
        exit(1);
    }
    if(argc == 2){
        file_path = argv[argc-1];
    }
    if(argc == 3){
        file_path = argv[argc-2];
    }

    pthread_t t[HASH_ALGOS_NUMBERS];
    int status;
    int *hash_algo_index = NULL;
    for(int i=0 ; i<HASH_ALGOS_NUMBERS ; i++){
        hash_algo_index = malloc(sizeof(int));
        *hash_algo_index = i;
        hashes[*hash_algo_index] = malloc(SHA512_DIGEST_LENGTH * sizeof(unsigned char));
        memset(hashes[*hash_algo_index], '\0', SHA512_DIGEST_LENGTH);

        status = pthread_create(
            &t[*hash_algo_index], 
            NULL, 
            hash_routine, 
            (void *)hash_algo_index
        );

        if(status != 0){
            printf("ERROR pthread_create failed %s %d\n", __FUNCTION__, __LINE__);
            exit(1);
        }
    }

    for(int i=0 ; i<HASH_ALGOS_NUMBERS ; i++){
        pthread_join(t[i], NULL);
    }    

    hash_value_print();

    if(argc == 2){
        return 0;
    }

    hash_value_compare(argv[argc-1]);

    // endwin();
    return 0;
}