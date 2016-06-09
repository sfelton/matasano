#ifndef DECODE_ENCODE_H
#define DECODE_ENCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

//Decode Methods
int decode_hex(unsigned char* output_data, char* input_string);
int decode_base64(unsigned char** output_data, char* input_string);
int decode_base64_from_file(unsigned char** output_data, char* file_name);

//Encode Methods
char* encode_base64(unsigned char* data, size_t length);
char* encode_hex(unsigned char* data, size_t length);

//Helper Methods
size_t get_base64_decoded_length(const char* input);



#endif //#ifndef DECODE_ENCODE_H
