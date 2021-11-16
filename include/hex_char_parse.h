#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md4.h>
#include <openssl/md5.h>


int hexchar_to_int_parse(unsigned char ch);

int haxstr_to_hexvalue_parser(unsigned char *str);

unsigned char * convert_hash_str_to_hash_value(char *input_hash);