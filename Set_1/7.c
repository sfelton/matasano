#include "decode_encode.h"
#include "crypto_lib.h"

char* encrypted_file = "files/7.txt";
unsigned char KEY[] = "YELLOW SUBMARINE";

int main(int argc, char* argv[]){
    printf("~~~~~~~~AES in ECB MODE~~~~~~~~\n");

    //Read in file to memory
    char* file_b64;
    FILE* fp;
    int file_length = 0;
    fp = fopen(encrypted_file, "r");
    if (fp == NULL) {
        printf("ERROR: Cannot open encrypted file, %s\n", encrypted_file);
        return 1;
    }

    char* line;
    ssize_t read;
    size_t length;
    while ((read = getline(&line, &length, fp)) != -1){
        line = strsep(&line, "\n");
        file_length += strlen(line);
    }
    fseek(fp, 0, SEEK_SET);
    file_b64 = malloc(file_length);
    while ((read = getline(&line, &length, fp)) != -1){
        line = strsep(&line, "\n");
        strcat(file_b64, line);
    }
    fclose(fp);

    //Decode base64
    unsigned char* data;
    size_t data_length = get_base64_decoded_length(file_b64);
    decode_base64(&data, file_b64);

    //Decrypt data
    unsigned char* data_plain;
    aes_128_ecb_decrypt(&data_plain, data, KEY, data_length);

    /*
    int len;
    unsigned char* data_plain = malloc(data_length);
    EVP_CIPHER_CTX* ctx;

    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, KEY, NULL);
    EVP_DecryptUpdate(ctx, data_plain, &len, data, data_length);
    EVP_DecryptFinal_ex(ctx, data_plain + len, &len);

    printf("%s\n", data_plain);


    EVP_CIPHER_CTX_free(ctx);
    */
    printf("%s\n", data_plain);

    free(line);
    free(data);
    free(data_plain);
    free(file_b64);
    return 0;
}
