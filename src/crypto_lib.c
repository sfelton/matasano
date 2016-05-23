#include "crypto_lib.h"

int xor( unsigned char* ANS,
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
