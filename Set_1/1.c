#include "decode_encode.h"

// Final Answer
char* final_string="SSdtIGtpbGxpbmcgeW91ciBicmFpbiBs"
                   "aWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

// Starting Value
char* start_string="49276d206b696c6c696e6720796f757220627261696e206c"
                   "696b65206120706f69736f6e6f7573206d757368726f6f6d";

// Test Value
char* test_string="0123456789abcdef";

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
    free(encoded_string);

    printf("Final ans: %s\n", encoded_string);
    printf("Should be: %s\n", final_string);
    return 0;
}
