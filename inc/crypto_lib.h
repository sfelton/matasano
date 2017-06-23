#ifndef CRYPTO_LIB_H
#define CRYPTO_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include <openssl/evp.h>

//Constants
static const size_t AES_BLOCK_SIZE = 16;

//Tables
static const float english_letter_frequency[26] =
{ 0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,  // A-G
  0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,  // H-N
  0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,  // O-U
  0.00978, 0.02361, 0.00150, 0.01974, 0.00074, };                 // V-Z

static const unsigned char hamming_weight[256] =
{
#define B2(n) n,    n+1,    n+1,    n+2
#define B4(n) B2(n),B2(n+1),B2(n+1),B2(n+2)
#define B6(n) B4(n),B4(n+1),B4(n+1),B4(n+2)
        B6(0), B6(1), B6(1), B6(2)
};

//Methods

//XOR METHODS
int balanced_xor( unsigned char* ANS,
                  unsigned char* LHS,
                  unsigned char* RHS,
                  size_t size);
int repeated_xor( unsigned char* ANS, 
                   unsigned char* LHS, 
                   size_t LHS_length,
                   unsigned char* RHS,
                   size_t RHS_length);

// Block Ciphers
int ecb_128_decrypt(unsigned char** plaintext,
                    unsigned char* ciphertext,
                    unsigned char* key,
                    size_t ct_size);

int ecb_128_encrypt(unsigned char** ciphertext,
                    unsigned char* plaintext,
                    unsigned char* key,
                    size_t pt_size);

int cbc_128_decrypt(unsigned char** plaintext,
                    unsigned char* ciphertext,
                    unsigned char* key,
                    unsigned char* iv,
                    size_t ct_size);

int cbc_128_encrypt(unsigned char** ciphertext,
                    unsigned char* plaintext,
                    unsigned char* key,
                    unsigned char* iv,
                    size_t pt_size);

//ANALYSIS METHODS
float score_letter_frequency(char* string, size_t string_length);
float score_letter_frequency_adams_way(char* string, size_t string_length);
ssize_t hamming_distance(unsigned char* LHS, unsigned char* RHS, size_t size);

//HELPER & MISC METHODS
int generate_random_key(unsigned char** key, size_t length);



#endif //#ifndef CRYPTO_LIB_H
