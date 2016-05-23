#ifndef DECODE_ENCODE_H
#define DECODE_ENCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

//Decode Methods
int decode_hex(unsigned char* output_hex, char* input_string);

//Encode Methods
char* encode_base64(unsigned char* data, size_t length);
char* encode_hex(unsigned char* data, size_t length);



#endif //#ifndef DECODE_ENCODE_H
