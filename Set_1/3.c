#include "decode_encode.h"
#include "crypto_lib.h"

char* encrypted_string = "1b37373331363f78151b7f2b783431333d"
                         "78397828372d363c78373e783a393b3736";
char* test_string = "aabbccdd";

int main(int argc, char* argv[]) {
    printf("~~~~~~~~SINGLE BYTE XOR~~~~~~~~\n\n");    
    printf("Original String: %s\n\n", encrypted_string);

    size_t buf_size = strlen(encrypted_string)/2;
    unsigned char* buf = malloc(buf_size);
    decode_hex(buf, encrypted_string);

    /*
    unsigned char* result = malloc(buf_size);
    balanced_xor(result, buf, buf, buf_size);
    char* string = encode_hex(result, buf_size);
//    printf("string = %s\n", string);
    
    free(string);
    free(result);
    */




    unsigned char* result = malloc(buf_size);

    for (unsigned int i = 0; i < 256; ++i) {
        repeated_xor(result, buf, buf_size, (unsigned char *)&i, 1);
        char* xored_string = encode_hex(result, buf_size);
        printf("%02x: %s\n", i, xored_string);
        free(xored_string);
    }

    free(result);
    free(buf);

    return 0;
}
