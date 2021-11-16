

#ifndef __FILE_IO_H__
#define __FILE_IO_H__
#include "../include/file_io.h"
#endif  /*__FILE_IO_H__*/


char *file_path = NULL;


FILE *file_read_routine(void *file_path_str){
    char *file_path = (char *)file_path_str;

    FILE *fp = fopen(file_path, "r");
    if(fp == NULL){
        printf("ERROR fopen failed %s %d\n", __FUNCTION__, __LINE__);
        exit(1);
    }
    return fp;
}