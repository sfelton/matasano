#include "decode_encode.h"
#include "crypto_lib.h"
#include <float.h>

char* encrypted_string = "1b37373331363f78151b7f2b783431333d"
                         "78397828372d363c78373e783a393b3736";
char* test_string = "41414141";

int main(int argc, char* argv[]) {

//    size_t size = strlen(test_string)/2;
//    unsigned char* bufff = malloc(size);
//    decode_hex(bufff, test_string);
//    printf("DEBUG: %s\n", bufff);





    printf("~~~~~~~~SINGLE BYTE XOR~~~~~~~~\n\n");    
    printf("Original String: %s\n\n", encrypted_string);

    size_t buf_size = strlen(encrypted_string)/2;
    unsigned char* buf = malloc(buf_size);
    decode_hex(buf, encrypted_string);

    unsigned char* result = malloc(buf_size);

    float lowest_score = FLT_MAX;
    unsigned int lowest_score_key = 256;
    unsigned char* lowest_score_result = malloc(buf_size);
    for (unsigned int i = 0; i < 256; ++i) {
        repeated_xor(result, buf, buf_size, (unsigned char *)&i, 1);
        float score = score_letter_frequency((char *)result);
        char* xored_string = encode_hex(result, buf_size);
        if (score != 0 && score < lowest_score) {
            lowest_score = score;
            lowest_score_key = i;
            lowest_score_result = result;
//            printf("%02x: %s - %f\n", i, xored_string, score);
//            printf("%s\n", (char *)result );
        }
        free(xored_string);
    }
    printf("Key = %02x with score %f\n", lowest_score_key, lowest_score);
    printf("%s\n", lowest_score_result);

    free(lowest_score_result);

    free(result);
    free(buf);

    return 0;
}
