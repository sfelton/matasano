#include "decode_encode.h"
#include "crypto_lib.h"

char* encrypted_file = "files/10.txt";
unsigned char KEY[] = "YELLOW SUBMARINE";

int main(int arc, char* argv[]){
    printf("~~~~~~~~IMPLEMENT CBC MODE~~~~~~~~\n");

    //Read file into memory;
    unsigned char* ciphertext;
    decode_base64_from_file(&ciphertext, encrypted_file);

    return 0;
}
