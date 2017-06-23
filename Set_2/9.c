#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
/*
 * HOW TO USE
 *
 * Run the program with the Usage shown below and the output into xxd
 * This will show you the string that was used as input followed by the
 * appropriate padding
 *
 * Ex:
 * $> ./1 "YELLOW SUBMARINE" 20 | xxd
 * 00000000: 5945 4c4c 4f57 2053 5542 4d41 5249 4e45  YELLOW SUBMARINE
 * 00000010: 0404 0404                                ....
 *
 *
 *
 */
//    printf("~~~~~~~~IMPLIMENT PKCS#7 PADDING~~~~~~~~\n");

    if (argc != 3) {
        printf("USAGE: ./1 <Block> <Padded Length>\n");
        return 1;
    }

    int original_length = strlen(argv[1]);
    int padded_length   = atoi(argv[2]);

    if (original_length > padded_length){
        printf("ERROR: Padded Length must be greater than original length\n");
        return 1;
    }
    unsigned int diff = padded_length - original_length;

//    printf("DEBUG: orig = %d\n", original_length);
//    printf("DEBUG: padd = %d\n", padded_length);

    char* output = malloc(padded_length + 1);
    memcpy(output, argv[1], original_length);

    for(unsigned int i = 0; i < diff; i++) {
//        printf("Printing at %d\n", original_length + i);
//        sscanf((char*)&diff, "%1s", output + (original_length + i));
        sscanf((char*)&diff, "%c", output + (original_length + i));
    }

    output[padded_length] = '\0';

    printf("%s", output);
    free(output);

    return 0;
}
