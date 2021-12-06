#include "../Headers/Aristocrat.h"

int GeneratePOTD (BYTE * Key, BYTE nKey)
{
	if (nKey < 4 || nKey > 10)
		Fatal("Seed value must be between 4 and 10 characters", NULL);
		
	BYTE Seed [10];
	
	memcpy (Seed, Key, nKey);
		
	if (nKey < 10) {
		for (int filler = nKey; filler < 10; filler ++) {
			memcpy (Seed + filler, Key + (filler - nKey), 1);
		}
	}

	time_t currentEpoch = time (NULL);
	struct tm * CurrentTime = localtime(&currentEpoch);
	
	BYTE Year		=		(CurrentTime -> tm_year + 1900) % 100;
	BYTE Month		=		CurrentTime -> tm_mon + 1;
	BYTE Day		=		CurrentTime -> tm_mday;
	BYTE WeekDay	=		CurrentTime -> tm_wday;
	
	if (!WeekDay)
		WeekDay 	= 		6;
	else
		WeekDay 	-=		1;
		
	BYTE ArrayFive [11] = {
		DateMatrix[WeekDay][0],		DateMatrix[WeekDay][1],
		DateMatrix[WeekDay][2],		DateMatrix[WeekDay][3],
		DateMatrix[WeekDay][4],		Day
	};
	
	if (Year + Month - Day < 0)
		ArrayFive[6] = 		(Year + Month - Day + 36) % 36;
	else
		ArrayFive[6] =		(Year + Month - Day) % 36;
		
	ArrayFive[7]	=		(3 + (Year + Month) % 12) * Day % 37 % 36;
	
	BYTE ArraySix[11] = {
			(BYTE) (Seed[0] % 36), (BYTE) (Seed[1] % 36),
            (BYTE) (Seed[2] % 36), (BYTE) (Seed[3] % 36),
            (BYTE) (Seed[4] % 36), (BYTE) (Seed[5] % 36),
            (BYTE) (Seed[6] % 36), (BYTE) (Seed[7] % 36)
	};
	
	BYTE checkByte;

    BYTE ArraySeven[11] = {
            (BYTE) ((ArrayFive[0] + ArraySix[0]) % 36), (BYTE) ((ArrayFive[1] + ArraySix[1]) % 36),
            (BYTE) ((ArrayFive[2] + ArraySix[2]) % 36), (BYTE) ((ArrayFive[3] + ArraySix[3]) % 36),
            (BYTE) ((ArrayFive[4] + ArraySix[4]) % 36), (BYTE) ((ArrayFive[5] + ArraySix[5]) % 36),
            (BYTE) ((ArrayFive[6] + ArraySix[6]) % 36), (BYTE) ((ArrayFive[7] + ArraySix[7]) % 36),
    };

    ArraySeven[8] = (BYTE) ((ArraySeven[0] + ArraySeven[1] + ArraySeven[2] + ArraySeven[3] + ArraySeven[4] + ArraySeven[5] + ArraySeven[6] + ArraySeven[7]) % 36);
    checkByte = ArraySeven[8] % 6;
    ArraySeven[9] = (BYTE) round(pow((double) checkByte, 2.0));

    BYTE ArrayEight[11] = {
            ArraySeven[MatrixTwo[checkByte][0]], ArraySeven[MatrixTwo[checkByte][1]],
            ArraySeven[MatrixTwo[checkByte][2]], ArraySeven[MatrixTwo[checkByte][3]],
            ArraySeven[MatrixTwo[checkByte][4]], ArraySeven[MatrixTwo[checkByte][5]],
            ArraySeven[MatrixTwo[checkByte][6]], ArraySeven[MatrixTwo[checkByte][7]],
            ArraySeven[MatrixTwo[checkByte][8]], ArraySeven[MatrixTwo[checkByte][9]]
    };

    BYTE ArrayNine[11] = {
            (Seed[0] + ArrayEight[0]) % 36, (Seed[1] + ArrayEight[1]) % 36,
            (Seed[2] + ArrayEight[2]) % 36, (Seed[3] + ArrayEight[3]) % 36,
            (Seed[4] + ArrayEight[4]) % 36, (Seed[5] + ArrayEight[5]) % 36,
            (Seed[6] + ArrayEight[6]) % 36, (Seed[7] + ArrayEight[7]) % 36,
            (Seed[8] + ArrayEight[8]) % 36, (Seed[9] + ArrayEight[9]) % 36,
    };

	printf ("Password for: %d/%d/%d: ", Day, Month, Year);
	
    printf("%c%c%c%c%c%c%c%c%c%c\r\n",
           Keyspace[ArrayNine[0]], Keyspace[ArrayNine[1]],
           Keyspace[ArrayNine[2]], Keyspace[ArrayNine[3]],
           Keyspace[ArrayNine[4]], Keyspace[ArrayNine[5]],
           Keyspace[ArrayNine[6]], Keyspace[ArrayNine[7]],
           Keyspace[ArrayNine[8]], Keyspace[ArrayNine[9]]);
           
}

int Seed_Decryptor (BYTE * EncryptedSeed, BYTE nEncryptedSeed, BYTE * CleartextSeed, int * nCleartextSeed)
{
	int Status, TempLength;

    EVP_CIPHER_CTX * Context = EVP_CIPHER_CTX_new();

    if (!Context)
        Fatal("Error Creating Context!", NULL);

    Status = EVP_DecryptInit_ex(Context, EVP_des_cbc(), NULL, SeedKey, NULL);

    EVP_CIPHER_CTX_set_padding(Context, 0);

    if (!Status)
        Fatal("Error initializing Context!", Context);

    Status = EVP_DecryptUpdate(Context, CleartextSeed, nCleartextSeed, EncryptedSeed, nEncryptedSeed);

    if (!Status)
        Fatal("Error Decrypting Message!", Context);

    Status = EVP_DecryptFinal(Context, CleartextSeed + *nCleartextSeed, &TempLength);
    if (!Status)
        Fatal("Error Decrypting Final Block!", Context);

    nCleartextSeed += TempLength;

    EVP_CIPHER_CTX_free(Context);

    return 0;
}

int Seed_Encryptor (BYTE * Input, BYTE InputLength, BYTE * Output, int  * OutputLength)
{
	BYTE CleartextSeed[10] = { 0 };
	
	if (InputLength > 10)
		memcpy(CleartextSeed, Input, 10);
	else
		memcpy(CleartextSeed, Input, InputLength);
		
	
    EVP_CIPHER_CTX * Context = EVP_CIPHER_CTX_new();

    int Status, TempLength;

    if (!Context)
        Fatal("Error creating Cipher Context!", NULL);

    Status = EVP_EncryptInit_ex(Context, EVP_des_cbc(), NULL, SeedKey, NULL);

    EVP_CIPHER_CTX_set_padding(Context, 0);

    if (!Status) {
        Fatal("Error Initializing Context!", Context);
    }

    Status = EVP_EncryptUpdate(Context, Output, OutputLength, CleartextSeed, 8);

    if (!Status)
        Fatal("Error Encrypting Message!", Context);

    Status = EVP_EncryptFinal(Context, Output + *OutputLength, &TempLength);
    if (!Status)
        Fatal("Error Encrypting the Final Block!", Context);

    OutputLength += TempLength;

    EVP_CIPHER_CTX_free(Context);

    return 0;

}

void Fatal (const char * Message, EVP_CIPHER_CTX * Context) {
	perror(Message);
	
	if (Context != NULL)
		EVP_CIPHER_CTX_free(Context);
		
	exit(1);
}
