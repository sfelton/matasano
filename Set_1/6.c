#include "decode_encode.h"
#include "crypto_lib.h"

char* encrypted_file = "files/6.txt";

int main(int argc, char* argv[]){
    printf("~~~~~~~~BREAK REPEATING KEY XOR~~~~~~~~\n");

    //Read in file to memory
    char* file_b64;
    FILE* fp;
    int file_length;
    fp = fopen(encrypted_file, "rb");
    if (fp == NULL){
        printf("ERROR: Cannot open encrypted file, %s\n", encrypted_file);
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    file_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    file_b64 = malloc(file_length);
    fread(file_b64, 1, file_length, fp);

    fclose(fp);

    printf("%s\n", file_b64);
    
    //Decode base64 into memory
    unsigned char* data;
    decode_base64(&data, file_b64);
    
    printf("\n%p: %s\n", data, data);

    /*
    //TEST: Hamming Distance
    char* string1 = "00";
    char* string2 = "f9";

    unsigned char* xs1 = malloc(1);
    unsigned char* xs2 = malloc(1);

    decode_hex(xs1, string1);
    decode_hex(xs2, string2);

    int hd;
    hd = hamming_distance(xs1, xs2, 1);

    printf("Hamming Distance = %d\n", hd);
    
    free(xs1);
    free(xs2);
    */

    free(data);
    free(file_b64);
    return 0;
}
