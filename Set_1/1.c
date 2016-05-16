#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int main(int argc, char* argv[]) {
    printf("Starting Value: %s\n", start_string);

    unsigned char* decoded_hex = malloc(strlen(start_string)/2);
    if (decode_hex(decoded_hex, start_string) <= 0) {
        printf("ERROR main: couldn't decode hex string\n");
        free(decoded_hex);
        return 1;
    }
    free(decoded_hex);
    return 0;
}
