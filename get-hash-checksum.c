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
#include <ncurses.h>
#include "libget-hash-checksum.h"



// unsigned char *hashes[4];   // for containing hash value
// char *file_path = NULL; // the path of file that would be hashed
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  



void *hash_routine(void *index){
    int status = pthread_mutex_lock(&mutex);
    if(status != 0){
        printf("ERROR pthread_mutex_lock failed %s %d\n", __FUNCTION__, __LINE__);
        exit(1);
    }
    
    unsigned char buf[BUF_SIZE];
    size_t len;
    int DIGEST_LEN;
    int i = *((int *) index);
    FILE * fp = file_read_routine(file_path);
    switch(i){
        case SHA1:{
            DIGEST_LEN = SHA_DIGEST_LENGTH;
            SHA_CTX ctx;
            SHA1_Init(&ctx);
            do{
                len = fread(buf, 1, BUF_SIZE, fp);
                SHA1_Update(&ctx, buf, len);
            }while(len == BUF_SIZE);
            SHA1_Final(buf, &ctx);
            break;
        }
        case SHA256:{
            DIGEST_LEN = SHA256_DIGEST_LENGTH;
            SHA256_CTX ctx;
            SHA256_Init(&ctx);
            do{
                len = fread(buf, 1, BUF_SIZE, fp);
                SHA256_Update(&ctx, buf, len);
            }while(len == BUF_SIZE);
            SHA256_Final(buf, &ctx);
            break;
        }
        case SHA512:{
            DIGEST_LEN = SHA512_DIGEST_LENGTH;
            SHA512_CTX ctx;
            SHA512_Init(&ctx);
            do{
                len = fread(buf, 1, BUF_SIZE, fp);
                SHA512_Update(&ctx, buf, len);
            }while(len == BUF_SIZE);
            SHA512_Final(buf, &ctx);
            break;
        }
        case MD5:{
            DIGEST_LEN = MD5_DIGEST_LENGTH;
            MD5_CTX ctx;
            MD5_Init(&ctx);
            do{
                len = fread(buf, 1, BUF_SIZE, fp);
                MD5_Update(&ctx, buf, len);
            }while(len == BUF_SIZE);
            MD5_Final(buf, &ctx);
            break;
        }
    }
    fclose(fp);
    memcpy(hashes[i], buf, DIGEST_LEN);
    status = pthread_mutex_unlock(&mutex);
    if(status != 0){
        printf("ERROR pthread_mutex_unlock failed %s %d\n", __FUNCTION__, __LINE__);
        exit(1);
    }
    return NULL;
}


int main(int argc, char *argv[]){
    // initscr();
    if(argc == 1){
        help();
        exit(1);
    }
    pthread_t t[4];
    int status;
    file_path = argv[argc-1];

    int *index = NULL;
    for(int i=0 ; i<4 ; i++){
        index = malloc(sizeof(int));
        *index = i;
        hashes[*index] = malloc(SHA512_DIGEST_LENGTH * sizeof(unsigned char));
        memset(hashes[*index], '\0', SHA512_DIGEST_LENGTH);
        status = pthread_create(&t[*index], NULL, hash_routine, (void *)index);
        if(status != 0){
            printf("ERROR pthread_create failed %s %d\n", __FUNCTION__, __LINE__);
            exit(1);
        }
    }

    for(int i=0 ; i<4 ; i++){
        pthread_join(t[i], NULL);
    }    

    int LEN;
    char *algo_name = NULL;
    for(int i=0 ; i<4 ; i++){
        switch(i){
            case SHA1:{
                LEN = SHA_DIGEST_LENGTH;
                algo_name = "SHA1";
                break;
            }
            case SHA256:{
                LEN = SHA256_DIGEST_LENGTH;
                algo_name = "SHA256";
                break;
            } 
            case SHA512:{
                LEN = SHA512_DIGEST_LENGTH;
                algo_name = "SHA512";
                break;
            }
            case MD5:{
                LEN = MD5_DIGEST_LENGTH;
                algo_name = "MD5";
                break;
            }
        }
        printf("%s\t:", algo_name);
        for(int j=0; j<LEN ; j++){
            printf("%02x", *(hashes[i]+j));
        }
        printf("\n");
    }
    // refresh();
    // getch();
    // endwin();
    return 0;
}