#ifndef ARRIS_H
#define  ARRIS_H

// Memcpy
#include <string.h>

// Time Operations
#include <time.h>

// Round, Pow
#include <math.h>

// Printf
#include <stdio.h>

// Exit
#include <stdlib.h>

// OpenSSL, DES Decryption
#include <openssl/evp.h>


#include "Sizes.h"

static BYTE DateMatrix [7][5] = {
		{15, 15, 24, 20, 24},
		{13, 14, 27, 32, 10},
		{29, 14, 32, 29, 24},
		{23, 32, 24, 29, 29},
		{14, 29, 10, 21, 29},
		{34, 27, 16, 23, 30},
		{14, 22, 24, 17, 13}
};

static BYTE MatrixTwo [6] [10] = {
		{0, 1, 2, 9, 3, 4, 5, 6, 7, 8},
		{1, 4, 3, 9, 0, 7, 8, 2, 5, 6},
		{7, 2, 8, 9, 4, 1, 6, 0, 3, 5},
		{6, 3, 5, 9, 1, 8, 2, 7, 4, 0},
		{4, 7, 0, 9, 5, 2, 3, 1, 8, 6},
		{5, 6, 1, 9, 8, 0, 4, 3, 2, 7}
};

static BYTE Keyspace [] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
		'W', 'X', 'Y', 'Z'
};

static BYTE SeedKey [8] = { 20, 157, 64, 213, 193, 46, 85, 2 };


// Password of the day generator. 

int GeneratePOTD(BYTE * Key, BYTE nKey);

// Decrypt an Encrypted seed

int Seed_Decryptor (BYTE * EncryptedSeed, BYTE nEncryptedSeed, BYTE * CleartextSeed, int * nCleartextSeed);

// Encrypt a Cleartext seed

int Seed_Encryptor (BYTE * Input, BYTE InputLength, BYTE * Output, int * OutputLength);


void Fatal(const char * Message, EVP_CIPHER_CTX * Context);

static BYTE * DefaultSeed = "MPSJKMDHAI";

#endif
