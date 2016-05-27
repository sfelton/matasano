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

