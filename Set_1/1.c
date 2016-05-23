#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

// Final Answer
char* final_string="SSdtIGtpbGxpbmcgeW91ciBicmFpbiBs"
                   "aWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

// Starting Value
char* start_string="49276d206b696c6c696e6720796f757220627261696e206c"
                   "696b65206120706f69736f6e6f7573206d757368726f6f6d";

// Test Value
char* test_string="0123456789abcdef";

/*
 * Given a hex string (input_string) and an output location (output_hex),
 * This function will take a hexidecimal encoded string, decode the string,
 * and place it into memory
 */
int decode_hex(unsigned char* output_hex, char* input_string) {
    // Length of hex string must be even
    if (strlen(input_string) % 2 != 0) {
        printf("ERROR decode_hex: string length not valid\n");
        return -1;
    }

    int byte_count =0;
    for(unsigned int pos = 0; pos < strlen(input_string)/2; pos++) {
//        printf("%c%c\n", input_string[pos * 2], input_string[(pos*2)+1]);
        sscanf(input_string+(pos*2), "%2hhx", output_hex+pos);
        byte_count++;
    }
    return byte_count;
}

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


int main(int argc, char* argv[]) {
    printf("Starting Value: %s\n", start_string);

    //Decode hex string and place in memory
    size_t data_length = strlen(start_string)/2;
    unsigned char* decoded_hex = malloc(data_length);
    printf("[ ] Decoding hex string...");
    if (decode_hex(decoded_hex, start_string) <= 0) {
        printf("\r[X\n");
        printf("ERROR main: couldn't decode hex string\n");
        free(decoded_hex);
        return 1;
    }
    printf("\r[*]\n");

    //Encode memory into a base64 string
    printf("[ ] Encoding to base64...");
    char* encoded_string = encode_base64(decoded_hex, data_length);

    printf("\r[*]\n");
    free(decoded_hex);

    printf("Final ans: %s\n", encoded_string);
    printf("Should be: %s\n", final_string);
    return 0;
}
