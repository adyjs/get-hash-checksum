


#ifndef __FILE_IO_H__
#define __FILE_IO_H__
#include "../include/hex_char_parse.h"
#endif  /*__FILE_IO_H__*/





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
