

#ifndef __HASH_COMPARE_H__
#define __HASH_COMPARE_H__
#include "../include/hash_compare.h"
#include "../include/hash_config.h"
#include "../include/hex_char_parse.h"

#endif  /*__HASH_COMPARE_H__*/




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
