#include "decode_encode.h"
#include "crypto_lib.h"

char* encrypted_file = "files/10.txt";
unsigned char KEY[] = "YELLOW SUBMARINE";
char* IV_hex = "00000000000000000000000000000000";

int main(int arc, char* argv[]){
    printf("~~~~~~~~IMPLEMENT CBC MODE~~~~~~~~\n");

    //Read file into memory;
    unsigned char* ciphertext;
    size_t length;
    length = decode_base64_from_file(&ciphertext, encrypted_file);

    //Decode Initialization Vector into Memory
    unsigned char* IV;
    IV = malloc(strlen(IV_hex)/2);
    decode_hex(IV, IV_hex);

    //Decrypt the file in CBC mode
    unsigned char* plaintext;
    cbc_128_decrypt(&plaintext, ciphertext, KEY, IV, length);

    printf("%s\n", plaintext);


    free(IV);
    free(ciphertext);
    free(plaintext);

    return 0;
}
