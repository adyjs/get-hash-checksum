
// hash algo index
#define MD4 0
#define MD5 1
#define SHA1 2
#define SHA224 3
#define SHA256 4
#define SHA384 5
#define SHA512 6

#define HASH_ALGOS_NUMBERS 7


#define BUF_SIZE 128    // fread buffer size for hash function digest

extern unsigned char *hashes[HASH_ALGOS_NUMBERS];
