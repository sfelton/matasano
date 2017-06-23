#include "crypto_lib.h"
#include "decode_encode.h"

unsigned char plain[] = "Two roads diverged in a yellow wood,\n"
                        "And sorry I could not travel both\n"
                        "And be one traveler, long I stood\n"
                        "And looked down one as far as I could\n"
                        "To where it bent in the undergrowth;\n"
                        "Then took the other, as just as fair,\n"
                        "And having perhaps the better claim,\n"
                        "Because it was grassy and wanted wear;\n"
                        "Though as for that the passing there\n"
                        "Had worn them really about the same,\n"
                        "And both that morning equally lay\n"
                        "In leaves no step had trodden black.\n"
                        "Oh, I kept the first for another day!\n"
                        "Yet knowing how way leads on to way,\n"
                        "I doubted if I should ever come back.\n"
                        "I shall be telling this with a sigh\n"
                        "Somewhere ages and ages hence:\n"
                        "Two roads diverged in a wood, and I-\n"
                        "I took the one less traveled by,\n"
                        "And that has made all the difference.";

unsigned char key[] = "YELLOW SUBMARINE";
unsigned char iv[]  = "0123456789abcdeF";

int main(int argc, char* argv[]){

    unsigned char* ciphertext;
    unsigned char* plaintext;
    int length;
    int dec_len;

    printf("%s\n", plain);
    printf("%lu\n", strlen((char*)plain));

    length = cbc_128_encrypt(&ciphertext, plain, key, iv, strlen((char*)plain));
    dec_len = cbc_128_decrypt(&plaintext, ciphertext, key, iv, length);
    plaintext[dec_len] = '\0';

    printf("DEBUG: length = %d\n", length);
    printf("DEBUG: declen= %d\n", dec_len);
    printf("%s\n", plaintext);
    free(plaintext);
    free(ciphertext);
    return 0;
}
