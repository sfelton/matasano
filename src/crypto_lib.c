#include "crypto_lib.h"


/*
 * XOR METHODS
 */

int balanced_xor( unsigned char* ANS,
         unsigned char* LHS, 
         unsigned char* RHS,
         size_t size)
{
    unsigned char* curr_ptr = ANS;
    for (size_t i = 0; i < size; ++i) {
        *curr_ptr = *(LHS+i)^*(RHS+i);
        ++curr_ptr;
    }
    return 0;
}

int repeated_xor(  unsigned char* ANS,
                   unsigned char* LHS,
                   size_t LHS_length,
                   unsigned char* RHS,
                   size_t RHS_length)
{
    //Check which side is larger and make sure it is set to LHS
    if ( LHS_length < RHS_length ) {
        unsigned char* temp = RHS;
        RHS=LHS;
        LHS=temp;

        size_t temp_length = RHS_length;
        RHS_length = LHS_length;
        LHS_length = temp_length;
    }

    /* This case should be handled by truncating the key on last pass
    //Check that RHS divides into LHS evenly
    if (LHS_length%RHS_length != 0) {
        printf("ERROR: repeating_xor: cannot repeat even number of times\n");
        return 1;
    }
    */

    unsigned int num_loops = LHS_length/RHS_length;
    if (LHS_length%RHS_length != 0) num_loops++;
    unsigned char* curr_ptr = ANS;
    for (unsigned int i = 0; i < num_loops; ++i) {
        if ((i+1)*RHS_length <= LHS_length) {
            balanced_xor(curr_ptr + (i*RHS_length), LHS + (i*RHS_length), RHS, RHS_length);
        } else {
            balanced_xor(curr_ptr + (i*RHS_length), LHS + (i*RHS_length), RHS, LHS_length-(i*RHS_length));
        }
    }

    return 0;
}

/*
 * ANALYSIS
 */

//http://crypto.stackexchange.com/questions/30209/developing-algorithm-for-detecting-plain-text-via-frequency-analysis
float score_letter_frequency(char* string, size_t string_length) {
    //Check that strlen matches string_length, it is possible to have a null
    //  byte in the middle of a decrypted string that can throw off resulst
    if (string_length != strlen(string)) return FLT_MAX;

    //Get a count of all the letters
    unsigned int num_letters = 0;
    unsigned int ignored = 0;
    unsigned int letter_count[26] = {0};
    for (unsigned int i=0; i < string_length; ++i){
        char c = string[i];
        if (c >= 'a' && c <= 'z') {
            letter_count[c-97]++;
            num_letters++;
        }
        else if (c >= 'A' && c <= 'Z') {
            letter_count[c-65]++;
            num_letters++;
        }
        else if (c >= ' ' && c <= '~') ignored++;
        else if (c == 9 || c == 10 || c == 13 ) ignored++;
        else return FLT_MAX;
    }

    //Do chi squared test to generate score
    float chi2 = 0;
    for (unsigned int i = 0; i < 26; ++i) {
        float expected = english_letter_frequency[i]*(string_length-ignored);
        if (expected != 0) {
            float difference = expected-letter_count[i];
            chi2 += ((difference*difference)/expected);
        }
    }

    return chi2;
}

float score_letter_frequency_adams_way(char* string, size_t string_length) {
    float score = 0; 

    for (unsigned int i=0; i < string_length; ++i){
        char c = string[i];
        if (c >= 'a' && c <= 'z') score += english_letter_frequency[c-97];
        else if (c >= 'A' && c <= 'Z') score += english_letter_frequency[c-65];
        else if (c >= ' ' && c <= '~');
        else if (c == 9 || c == 10 || c == 13 );
        else score -= 0.5;
        
    }
    return score;
}

ssize_t hamming_distance(unsigned char* LHS, unsigned char* RHS, size_t size){

    //Operating under the assumption that LHS and RHS are the same size

    unsigned char* xored = malloc(size);
    balanced_xor(xored, LHS, RHS, size);
    int total = 0;
    for (unsigned int i = 0; i < size; ++i){
       total += hamming_weight[(int)*(xored+i)];
    }

    free(xored);
    return total;
}

