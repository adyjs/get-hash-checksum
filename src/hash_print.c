
#ifndef __HASH_PRINT_H__
#define __HASH_PRINT_H__
#include "../include/hash_print.h"
#include "../include/hash_config.h"
#include "../include/file_io.h"
#endif /*__HASH_PRINT_H__*/




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

