#ifndef CRYPTO_LIB_H
#define CRYPTO_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int balanced_xor( unsigned char* ANS,
                  unsigned char* LHS,
                  unsigned char* RHS,
                  size_t size);
int repeated_xor( unsigned char* ANS, 
                   unsigned char* LHS, 
                   size_t LHS_length,
                   unsigned char* RHS,
                   size_t RHS_length);

float score_letter_frequency(char* string);





#endif //#ifndef CRYPTO_LIB_H
