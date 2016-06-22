#include "decode_encode.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

/*
 * DECODE METHODS
 */

int decode_hex(unsigned char* output_data, char* input_string) {
    // Length of hex string must be even
    if (strlen(input_string) % 2 != 0) {
        printf("ERROR decode_hex: string length not valid\n");
        return -1;
    }

    int byte_count =0;
    for(unsigned int pos = 0; pos < strlen(input_string)/2; pos++) {
        sscanf(input_string+(pos*2), "%2hhx", output_data+pos);
        byte_count++;
    }
    return byte_count;
}

int decode_base64(unsigned char** output_data, char* input_string){
    BIO *b64, *bmem;

    size_t data_length = get_base64_decoded_length(input_string);
    *output_data = malloc(data_length);

    bmem = BIO_new_mem_buf(input_string, -1);
    b64  = BIO_new(BIO_f_base64());

    bmem = BIO_push(b64, bmem);

    BIO_set_flags(bmem, BIO_FLAGS_BASE64_NO_NL);
    BIO_read(bmem, *output_data, strlen(input_string));
 //   BIO_flush(bmem);
    BIO_set_close(bmem, BIO_NOCLOSE);
    BIO_free_all(bmem);

//    printf("DEBUG: %p: %s\n", *output_data, *output_data);

    return 0;
}

int decode_base64_from_file(unsigned char** output_data, char* file_name){
    
    //Read in file to memory
    char* file_b64;
    FILE* fp;
    int file_length = 0;
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("ERROR: Cannot open encrypted file, %s\n", file_name);
        return -1;
    }

    char* line = NULL;
    ssize_t read;
    size_t length;
    while ((read = getline(&line, &length, fp)) != -1){
        line = strsep(&line, "\n");
        file_length += strlen(line);
    }
    fseek(fp, 0, SEEK_SET);
    file_b64 = malloc(file_length);
    while ((read = getline(&line, &length, fp)) != -1){
        line = strsep(&line, "\n");
        strcat(file_b64, line);
    }
    fclose(fp);
    free(line);

    //Decode base64
    size_t data_length = get_base64_decoded_length(file_b64);
    decode_base64(output_data, file_b64);

    free(file_b64);
    
    return data_length;
}

/*
 * ENCODE METHOS
 */

char* encode_base64(unsigned char* data, size_t length) {
    BIO *bmem, *b64;
    BUF_MEM *bufmem;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());

    b64 = BIO_push(b64, bmem);

    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, data, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bufmem);
    BIO_set_close(b64, BIO_NOCLOSE);
    BIO_free_all(b64);

    return bufmem->data;

}

char* encode_hex(unsigned char* data, size_t length) {
    char* final = malloc((length*2)+1);
    for (size_t i = 0; i < length; ++i) {
        sprintf(final+(i*2), "%02x", *(data+i));
    }
    *(final+(length*2)) = '\0';
    return final;
}


/*
 * HELPER METHODS
 */

size_t get_base64_decoded_length(const char* input){
    size_t length = strlen(input);
    size_t padding = 0;
    if (input[length-1] == '=' && input[length-2] == '=') padding = 2;
    else if (input[length-1] == '=') padding = 1;

    return ((length*3)/4)-padding;
}
