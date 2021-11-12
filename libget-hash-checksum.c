#include <stdio.h>
#include <stdlib.h>
// #include <openssl/sha.h>
#include <pthread.h>
#include "libget-hash-checksum.h"

unsigned char *hashes[HASH_ALGOS_NUMBERS];
char *file_path = NULL;

void help(void){
    printf("\nUSAGE : \n");
    printf("get-hash-checksum   Path/To/File    [User Input Hash Value For Comparing]\n");
    printf("\nHash functions :\n");
    // printf("- MD2 :\n");
    printf("- MD4 :\n");
    printf("- MD5 :\n");
    printf("- SHA1 :\n");
    printf("- SHA224 :\n");
    printf("- SHA256 :\n");
    printf("- SHA384 :\n");
    printf("- SHA512 :\n");
    printf("\n");
}

FILE *file_read_routine(void *file_path_str){
    char *file_path = (char *)file_path_str;

    FILE *fp = fopen(file_path, "r");
    if(fp == NULL){
        printf("ERROR fopen failed %s %d\n", __FUNCTION__, __LINE__);
        exit(1);
    }
    return fp;
}