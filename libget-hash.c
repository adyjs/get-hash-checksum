#include <stdio.h>
#include <stdlib.h>



// typedef struct _pack{
//     char *file_path;
//     void *hash;
// }Pack;

void help(void){
    printf("\nUSAGE : \n");
    printf("get-hash [option_1 | option_2] Path/To/file\n");
    printf("\noptions:\n");
    printf("  sha1:\n");
    printf("  sha256:\n");
    printf("  sha512:\n");
    printf("  md5:\n");
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