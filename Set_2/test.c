#include "crypto_lib.h"
#include "decode_encode.h"

unsigned char plain[] = "This is it";
unsigned char key[] = "YELLOW SUBMARINE";

int main(int argc, char* argv[]){

    unsigned char* ciphertext;
    unsigned char* plaintext;
    int length;

    length = aes_128_ecb_encrypt(&ciphertext, plain, key, 10);
    aes_128_ecb_decrypt(&plaintext, ciphertext, key, length);

    printf("DEBUG: length = %d\n", length);
    printf("%s\n", plaintext);
    free(plaintext);
    free(ciphertext);
    return 0;
}
