#include "decode_encode.h"
#include "crypto_lib.h"

char* plaintext = "Burning 'em, if you ain't quick and nimble "
                  "I go crazy when I hear a cymbal";

char* key = "ICE";

char* correct_ans = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d633"
                    "43c2a26226324272765272a282b2f20430a652e2c652a3124333a"
                    "653e2b2027630c692b20283165286326302e27282f";

int main(int argc, char* argv[]){
    printf("~~~~~~~~IMPLEMENT REPEATING-KEY XOR~~~~~~~~\n");

    unsigned char* ciphertext = malloc(strlen(plaintext));
    repeated_xor( ciphertext, 
                  (unsigned char*)plaintext, strlen(plaintext), 
                  (unsigned char*)key, strlen(key));

    char* encoded_ct = encode_hex(ciphertext, strlen(plaintext));

    printf("%s\n", encoded_ct);
    printf("-----------------------------\n");
    printf("%s\n", correct_ans);

    free(encoded_ct);
    free(ciphertext);
    return 0;
}
