#include "decode_encode.h"
#include "crypto_lib.h"

// Starting Values
char* LHS="1c0111001f010100061a024b53535009181c";
char* RHS="686974207468652062756c6c277320657965";

//Final Answer
char* ANS="746865206b696420646f6e277420706c6179";

int main(int argc, char* argv[]) {
    printf("~~~~~FIXED XOR~~~~\n\n");

    size_t LHS_size = strlen(LHS)/2;
    size_t RHS_size = strlen(RHS)/2;
    unsigned char* LHS_data = malloc(LHS_size);
    unsigned char* RHS_data = malloc(RHS_size);
    decode_hex(LHS_data, LHS);
    decode_hex(RHS_data, RHS);

    if (LHS_size != RHS_size) {
        printf("ERROR: LHS and RHS length do not match");
        return 1;
    }

    unsigned char* ans_data = malloc(LHS_size);
    xor(ans_data, LHS_data, RHS_data, LHS_size);
    char* ans = encode_hex(ans_data, LHS_size);

    printf("    %s\n", LHS);
    printf("XOR %s\n", RHS);
    printf("---------------------------------------\n");
    printf("    %s\n", ans);
    printf("---------------------------------------\n");
    printf("ANS=%s\n\n", ANS);


    free(LHS_data);
    free(RHS_data);
    free(ans_data);
    free(ans);
}
