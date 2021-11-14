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
        case MD4:{
            DIGEST_LEN = MD4_DIGEST_LENGTH;
            MD4_CTX ctx;
            MD4_Init(&ctx);
            do{
                len = fread(buf, 1, BUF_SIZE, fp);
                MD4_Update(&ctx, buf, len);
            }while(len == BUF_SIZE);
            MD4_Final(buf, &ctx);
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
        case SHA224:{
            DIGEST_LEN = SHA224_DIGEST_LENGTH;
            SHA256_CTX ctx;     // SHA224 CTX same as SHA256
            SHA224_Init(&ctx);
            do{
                len = fread(buf, 1, BUF_SIZE, fp);
                SHA224_Update(&ctx, buf, len);
            }while(len == BUF_SIZE);
            SHA224_Final(buf, &ctx);
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
        case SHA384:{
            DIGEST_LEN = SHA384_DIGEST_LENGTH;
            SHA512_CTX ctx;     // SHA384 CTX same as SHA512
            SHA384_Init(&ctx);
            do{
                len = fread(buf, 1, BUF_SIZE, fp);
                SHA384_Update(&ctx, buf, len);
            }while(len == BUF_SIZE);
            SHA384_Final(buf, &ctx);
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


int hexchar_to_int_parse(unsigned char ch){
    if(ch >= '0' && ch <= '9'){
        return ch - '0';
    }
    if(ch >= 'A' && ch <= 'F'){
        return (ch - 'A' + 10);
    }
    if(ch >= 'a' && ch <= 'f'){
        return (ch - 'a' + 10);
    }
    if(ch == ' '){
        // printf("ch : %c, %d\n", ch, ch);
        // printf("in space if\n");
        return 32;
    }
    return -1;
}

int haxstr_to_hexvalue_parser(unsigned char *str){
    int v1 = (int) hexchar_to_int_parse(*str);
    int v2 = (int) hexchar_to_int_parse(*(str+1));
    if(v1 == -1 || v2 == -1){
        printf("%c %d\n", *str, v1);
        printf("%c %d\n", *(str+1), v2);
        printf("ERROR str_to_hex parse failed in %s:%d\n", __FUNCTION__, __LINE__);
        printf("input hex character is out of range\n");
        printf("parse range : 0-9, A(a)-F(f)\n");
        printf("no special characters or space included\n");
        printf("please check the user input hash value string length or content\n");
        printf("\n");
        exit(1);
        // return -1;
    }
    return (v1*16)+(v2);

}

unsigned char * convert_hash_str_to_hash_value(char *input_hash){
    /*
        這邊的 input_hash 為使用者手動輸入，想要比對的雜湊值，此雜湊值為 string，
        
        把檔案 digest 之後算出之雜湊值，為 unsigned char 之數值，而非 string，
        unsigned char 把每一個 byte 之值以 %02x 的方式來解析成 hex，
        因此每一個 byte 可以解析成 2 個 hex 值來表示，
        之後再用 %02x 列印出來，因此看起來像是 2 個分別的字元

        因此這時我們想要把使用者手動輸入的雜湊值轉換回每一個 byte 的數值時，
        就必須反過來，把這個 input_hash 的每兩個字元看成一個 byte，
        把每兩個字元串接起來變成一個 hex string 在用 strtol() 解析為 %ld
        再存回去 unsigned char array 裡面，就會得到可以用 memcmp() 比對的 hash value
        
    */ 
    unsigned char *buf = malloc(SHA512_DIGEST_LENGTH * sizeof(unsigned char));
    memset(buf, '\0', SHA512_DIGEST_LENGTH);
    unsigned char temp[2];
    size_t len = strlen(input_hash)/2;

    // printf("len : %ld\n", strlen(input_hash));
    // printf("len/2 : %ld\n", strlen(input_hash)/2);

    int count = 0; 
    for(int i=0 ; i<len*2 ; i+=2){
        // printf("i : %d\n", i);
        memcpy(temp, input_hash+i, 2);
        // buf[count++] = strtoul(temp, NULL, 16);
        buf[count++] = haxstr_to_hexvalue_parser(temp);
    }

    printf("Hash Value That You Inputted\n");
    printf("----------------------------\n");
    printf("Digest Length : %ld\n", len);
    // printf("\n");
    // printf("\n");
    for(int i=0 ; i<len ; i++){
        printf("%02x", buf[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");

    return buf;
}


void hash_value_print(void){

    int DIGEST_LEN;
    char *algo_name = NULL;
    printf("\n\n");
    printf("Target File\t: %s\n", file_path);
    printf("------------------------------------------------\n");
    // printf("\n");
    for(int i=0 ; i<HASH_ALGOS_NUMBERS ; i++){
        switch(i){
            case MD4:{
                DIGEST_LEN = MD4_DIGEST_LENGTH;
                algo_name = "MD4";
                break;
            }
            case MD5:{
                DIGEST_LEN = MD5_DIGEST_LENGTH;
                algo_name = "MD5";
                break;
            }
            case SHA1:{
                DIGEST_LEN = SHA_DIGEST_LENGTH;
                algo_name = "SHA-1";
                break;
            }
            case SHA224:{
                DIGEST_LEN = SHA224_DIGEST_LENGTH;
                algo_name = "SHA-224";
                break;
            }
            case SHA256:{
                DIGEST_LEN = SHA256_DIGEST_LENGTH;
                algo_name = "SHA-256";
                break;
            } 
            case SHA384:{
                DIGEST_LEN = SHA384_DIGEST_LENGTH;
                algo_name = "SHA-384";
                break;
            }
            case SHA512:{
                DIGEST_LEN = SHA512_DIGEST_LENGTH;
                algo_name = "SHA-512";
                break;
            }
        }
        if(algo_name == NULL){
            printf("ERROR Hash print failed %s %d\n", __FUNCTION__, __LINE__);
            exit(1);
        }
        
        printf("%s\t:", algo_name);
        for(int j=0; j<DIGEST_LEN ; j++){
            printf("%02x", *(hashes[i]+j));
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
}


void hash_value_compare(char *unconfirmed_hash){
    int DIGEST_LEN = 0;
    int match = -1;
    unsigned char *cmpbuf = convert_hash_str_to_hash_value(unconfirmed_hash);
    for(int i=0 ; i<HASH_ALGOS_NUMBERS ; i++){
        if(i == MD4)
            DIGEST_LEN = MD4_DIGEST_LENGTH;
        if(i == MD5)
            DIGEST_LEN = MD5_DIGEST_LENGTH;
        if(i == SHA1)
            DIGEST_LEN = SHA_DIGEST_LENGTH;
        if(i == SHA224)
            DIGEST_LEN = SHA224_DIGEST_LENGTH;
        if(i == SHA256)
            DIGEST_LEN = SHA256_DIGEST_LENGTH;
        if(i == SHA384)
            DIGEST_LEN = SHA384_DIGEST_LENGTH;
        if(i == SHA512)
            DIGEST_LEN = SHA512_DIGEST_LENGTH;
        if(DIGEST_LEN == 0){
            printf("ERROR LEN setting failed %s %d\n", __FUNCTION__, __LINE__);
            exit(1);
        }
        if(memcmp(cmpbuf, hashes[i], DIGEST_LEN) == 0){
            match = i;
            break;
        }
    }
    
    printf("Hash Value Comparing Result\n");
    printf("---------------------------\n");
    switch(match){
        case MD4:{
            printf("It's Match with MD4 \n");
            break;
        }
        case MD5:{
            printf("It's Match with MD5 \n");
            break;
        }
        case SHA1:{
            printf("It's Match with SHA-1 \n");
            break;
        }
        case SHA224:{
            printf("It's Match with SHA-224 \n");
            break;
        }
        case SHA256:{
            printf("It's Match with SHA-256 \n");
            break;
        }
        case SHA384:{
            printf("It's Match with SHA-384 \n");
            break;
        }
        case SHA512:{
            printf("It's Match with SHA-512 \n");
            break;
        }
        default:
            printf("Does not Match Any.\n");
    }
    printf("\n");
    printf("\n");
    
}


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