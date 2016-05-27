#include "decode_encode.h"

/*
 * DECODE METHODS
 */

int decode_hex(unsigned char* output_hex, char* input_string) {
    // Length of hex string must be even
    if (strlen(input_string) % 2 != 0) {
        printf("ERROR decode_hex: string length not valid\n");
        return -1;
    }

    int byte_count =0;
    for(unsigned int pos = 0; pos < strlen(input_string)/2; pos++) {
        sscanf(input_string+(pos*2), "%2hhx", output_hex+pos);
        byte_count++;
    }
    return byte_count;
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
        sprintf(final+(i*2), "%02X", *(data+i));
    }
    *(final+(length*2)) = '\0';
    return final;
}
