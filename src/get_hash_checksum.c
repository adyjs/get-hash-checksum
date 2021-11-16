

#ifndef __GET_HASH_CHECKSUM_H__
#define __GET_HASH_CHECKSUM_H__

#include "../include/get_hash_checksum.h"
#include "../include/file_io.h"
#include "../include/hash_config.h"
#include "../include/mutex.h"
#endif /*__GET_HASH_CHECKSUM_H__*/



// unsigned char *hashes[4];   // for containing hash value
// char *file_path = NULL; // the path of file that would be hashed



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

