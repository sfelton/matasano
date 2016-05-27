#include "crypto_lib.h"

float english_letter_frequency[26] =
{ 0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,  // A-G
  0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,  // H-N
  0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,  // O-U
  0.00978, 0.02360, 0.00150, 0.01974, 0.00074, };                 // V-Z


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

int repeated_xor( unsigned char* ANS,
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

    //Check that RHS divides into LHS evenly
    if (LHS_length%RHS_length != 0) {
        printf("ERROR: repeating_xor: cannot repeat even number of times\n");
        return 1;
    }

    unsigned int num_loops = LHS_length/RHS_length;
    unsigned char* curr_ptr = ANS;
    for (unsigned int i = 0; i < num_loops; ++i) {
        balanced_xor(curr_ptr + (i*RHS_length), LHS + (i*RHS_length), RHS, RHS_length);
//        curr_ptr += RHS_length;
    }

    return 0;
}

/*
 * FREQUENCY ANALYSIS
 */

//http://crypto.stackexchange.com/questions/30209/developing-algorithm-for-detecting-plain-text-via-frequency-analysis
float score_letter_frequency(char* string){
    //Get a count of all the letters
    unsigned int num_letters = 0;
    unsigned int letter_count[26] = {0};
    for (unsigned int i=0; i < strlen(string); ++i){
        char c = string[i];
        if (c >= 'a' && c <= 'z') {
            letter_count[c-97]++;
            num_letters++;
        }
        else if (c >= 'A' && c <= 'Z') {
            letter_count[c-65]++;
            num_letters++;
        }
    }

    //Do chi squared test to generate score
    float chi2 = 0;
    for (unsigned int i = 0; i < 26; ++i) {
        float expected = english_letter_frequency[i]*strlen(string);
        float difference = expected-letter_count[i];
        if (expected != 0) chi2 += (float)((difference*difference)/expected);
    }

    return chi2;
}

