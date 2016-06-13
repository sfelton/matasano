#include "decode_encode.h"

char* encrypted_file = "files/8.txt";

int main(int argc, char* argv[]){
    printf("~~~~~~~~DETECT AES IN ECB MODE~~~~~~~~\n");

    //Only have to detect which one is encrypted, don't have to decrypt it
    
    //Open file
    FILE* fp;
    fp = fopen(encrypted_file, "r");
    if (fp == NULL) {
        printf("ERROR: Cannot open encrypted file, %s\n", encrypted_file);
        return 1;
    } 
    
    //Check each line for 16 byte repeating blocks,
    //the most repeating blocks win!
    int line_num = 1;
    int best_ln = -1;
    int best_eq = -1;
    int equal_blocks;
    char* curr_best_line;

    char* line;
    ssize_t read;
    size_t len;
    while ((read = getline(&line, &len, fp)) != -1){
        line = strsep(&line, "\n");
        equal_blocks = 0;

        char* block_a = malloc((16*2) + 1);
        char* block_b = malloc((16*2) + 1);
        for(int i = 0; i < strlen(line); i += 2*16){
            memcpy(block_a,line + i, 32);
            block_a[32] = '\0';

            for(int j = 0; j < strlen(line); j += 2*16){
                memcpy(block_b,line + j, 32);
                block_b[32] = '\0';
                if(!strcmp(block_a,block_b)&&i!=j) equal_blocks++;
//                printf("%s | %s\n", block_a, block_b);
            }
        }
        if (equal_blocks > best_eq){
            best_ln = line_num;
            best_eq = equal_blocks;
            curr_best_line = realloc(curr_best_line, len);
            memcpy(curr_best_line, line, len);
        }

        free(block_b);
        free(block_a);
        line_num++;
    }

    printf("Line %d: %s\n", best_ln, curr_best_line);
    free(line);
    free(curr_best_line);
    fclose(fp);


    return 0;
}
