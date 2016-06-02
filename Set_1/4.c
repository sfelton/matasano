#include "decode_encode.h"
#include "crypto_lib.h"

#include <stdlib.h>
#include <stdio.h>

char* string_file  = "files/4.txt";

int main(int argc, char* argv[]) {
    printf("~~~~~~~~DETECT SINGLE BYTE XOR~~~~~~~~\n\n");    

    FILE *fp;
    char* line = NULL;
    size_t len;
    ssize_t read;

    fp = fopen(string_file, "r");
    if (fp == NULL) {
        printf("ERROR: Cannot open file %s\n", string_file);
        return 1;
    }
    
    float GL_lowest_score = FLT_MAX;
    ssize_t GL_line_num = -1;
    unsigned int GL_lowest_score_key = 256;
    unsigned char* GL_lowest_score_result = malloc(30);

    //For each line in the file
    unsigned int line_num = 0;
    while((read = getline(&line, &len, fp)) != -1) {
        //Remove newline at end if neccessary
        line = strsep(&line, "\n");

//        printf("%zu: %s\n", strlen(line), line);

        //Decode the hex string into memory
        size_t buf_size = strlen(line)/2;
        unsigned char* buf = malloc(buf_size);
        decode_hex(buf, line);

        //Score each possilbe single byte key
        float lowest_score = FLT_MAX;
        unsigned int lowest_score_key;
        unsigned char* lowest_score_result = malloc(buf_size);
        unsigned char* result = malloc(buf_size);
        for (unsigned int i = 0; i < 256; ++i){
            repeated_xor(result, buf, buf_size, (unsigned char *)&i, 1);
            float score = score_letter_frequency((char *)result, buf_size);
            if (score != 0 && score < lowest_score) {
                lowest_score = score;
                lowest_score_key = i;
                memcpy(lowest_score_result, result, buf_size);
            }
        }

        //Check if any scores are better than the previous ones
        if (lowest_score < GL_lowest_score){
            GL_lowest_score = lowest_score;
            GL_lowest_score_key = lowest_score_key;
            memcpy(GL_lowest_score_result, lowest_score_result, buf_size);
            GL_line_num = line_num;
        }

        free(lowest_score_result);
        free(result);
        free(buf);

        line_num++;
    }
    //Print result
    printf("Key = 0x%02x (%c) with score %f\n", GL_lowest_score_key, GL_lowest_score_key, GL_lowest_score);
    printf("%zu: %s\n", GL_line_num, GL_lowest_score_result);

    free(GL_lowest_score_result);
    free(line);
    fclose(fp);
    return 0;
}
