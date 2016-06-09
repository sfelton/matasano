#include "decode_encode.h"
#include "crypto_lib.h"

char* encrypted_file = "files/6.txt";

int main(int argc, char* argv[]){
    printf("~~~~~~~~BREAK REPEATING KEY XOR~~~~~~~~\n");

    //Read in file to memory
    char* file_b64;
    FILE* fp;
    int file_length = 0;
    fp = fopen(encrypted_file, "r");
    if (fp == NULL){
        printf("ERROR: Cannot open encrypted file, %s\n", encrypted_file);
        return 1;
    }

    char* line;
    ssize_t read;
    size_t len;
    //Get length of file
    while ((read = getline(&line, &len, fp)) != -1){
        //Remove trailing newline
        line = strsep(&line, "\n");
        file_length += strlen(line);
    }
    fseek(fp, 0, SEEK_SET);
    file_b64 = malloc(file_length);
    while ((read = getline(&line, &len, fp)) != -1){
        //Remove trailing newline
        line = strsep(&line, "\n");
        strcat(file_b64, line);
    }
    
    /*
    fseek(fp, 0, SEEK_END);
    file_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    file_b64 = malloc(file_length);
    fread(file_b64, 1, file_length, fp);
    */

    fclose(fp);
    
    //Decode base64 into memory
    unsigned char* data;
    decode_base64(&data, file_b64);


    //Find the key size
    unsigned int KEYSIZE = 0;
    int hd;
    float normalized;
    float lowest = FLT_MAX;
    for (unsigned int key_size = 2; key_size <= 40; ++key_size){
        //Hamming Distance of every combination of 1st 4 blocks of key_size
        hd  = hamming_distance(data, data+(key_size), key_size);
        hd += hamming_distance(data, data+(2*key_size), key_size);
        hd += hamming_distance(data, data+(3*key_size), key_size);
        
        hd += hamming_distance(data+key_size, data+(2*key_size), key_size);
        hd += hamming_distance(data+key_size, data+(3*key_size), key_size);
        
        hd += hamming_distance(data+(2*key_size), data+(3*key_size), key_size);
        
        normalized = (float)hd/key_size;
        if (normalized < lowest) {
            lowest = normalized;
            KEYSIZE = key_size;
        }
//        printf("DEBUG: key size %d - hd %f\n", key_size, normalized);
    }

    if (KEYSIZE == 0) {
        printf("ERROR: Could not find a keysize\n");
        return 1;
    }
    
    printf("KEYSIZE = %d\n", KEYSIZE);

    //Allocate space for a key
    unsigned char* key = malloc(KEYSIZE);

    //Break each byte of the key individually
    for (unsigned int i = 0; i < KEYSIZE; ++i){
        //Create block of every ith KEYSIZE block
        size_t tb_size = get_base64_decoded_length(file_b64)/KEYSIZE;
        tb_size++;
//        if (i < get_base64_decoded_length(file_b64)%KEYSIZE) tb_size++;

        unsigned char* transposed_block = malloc(tb_size);
        unsigned int file_index = i;
        for (unsigned int j = 0; j < tb_size; ++j){
            memcpy(transposed_block+j,data+file_index,1);
            file_index += KEYSIZE;
        }

        //Find single byte key for transposed block
        float lowest_score = FLT_MAX;
        unsigned int lowest_score_key = 256;
        unsigned char* result = malloc(tb_size);
        for (unsigned int k = 0; k < 256; ++k){
            repeated_xor( result, 
                          transposed_block, tb_size, 
                          (unsigned char *)&k, 1);
            float score = score_letter_frequency((char *)result, tb_size);
            if (score != 0 && score < lowest_score){
                lowest_score = score;
                lowest_score_key = k;
            }
        }
        memcpy(key+i,&lowest_score_key,1);
        printf("INDEX %2d: %3d (%c)\n", i, lowest_score_key, lowest_score_key);


        free(result);
        free(transposed_block);
    }
    printf("%s\n", key);

    //Decrypt data
    unsigned char* decrypted_data = malloc(get_base64_decoded_length(file_b64));
    repeated_xor( decrypted_data,
                  data, get_base64_decoded_length(file_b64),
                  key, KEYSIZE);
    
    printf("%s\n", decrypted_data);

    free(key);

    free(data);
    free(file_b64);
    return 0;
}
