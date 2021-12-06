#include "Headers/Aristocrat.h"

void help(const char * filename) {
	puts("                                                                               ");
	puts("                           _         _                                   _     ");
	puts("     /\\                   (_)       | |                                 | |    ");
	puts("    /  \\     _ __   _ __   _   ___  | |_    ___     ___   _ __    __ _  | |_   ");
	puts("   / /\\ \\   | '__| | '__| | | / __| | __|  / _ \\   / __| | '__|  / _` | | __|  ");
	puts("  / ____ \\  | |    | |    | | \\__ \\ | |_  | (_) | | (__  | |    | (_| | | |_   ");
	puts(" /_/    \\_\\ |_|    |_|    |_| |___/  \\__|  \\___/   \\___| |_|     \\__,_|  \\__|  ");
	puts("                                                                               ");
	puts(" andrew.borg@minerva.com.mt                                       by Minerva IS");
    puts("                                                                               ");
	puts("Password of the Day (POTD) generator for Arris Cable Modems");
	
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	
	puts("Functions: ");
	puts("\tGenerate a Password of the Day using the -P switch.");
	puts("\tDecrypt an Arris CM seed using the -D switch.");
	puts("\tEncrypt a cleartext seed for use with Arris CMs using the -E switch.");
	
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	
	puts("Usage:");
	printf("\t %s -P [Custom Seed]\r\n", filename);
	printf("\t %s -D <Arris Encrypted Seed>\t\n", filename);
	printf("\t %s -E <Cleartext Seed>\t\n", filename);
	
	puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	
	puts("Examples:");
	printf("\t Generate POTD using the default Seed:\n\t\t  %s -P \r\n", filename);
	printf("\t Generate POTD using a custom Seed:\n\t\t %s -P MySeed \r\n", filename);
	printf("\t Encrypt a seed value for use with Arris CMs:\n\t\t %s -E Enc1Seed \r\n", filename);
	printf("\t Decrypt a seed value being used on Arris CMs:\n\t\t %s -D 0xF4BC50A0C5FC3B93 \r\n\r\n", filename);
	
}

int main (int argc, char ** argv)
{
	if (argc == 1) 
	{
		help(argv[0]);
		return 1;
	}
	else if (!strcmp(argv[1], "-P"))
	{
		if (argc > 2) 
		{
			printf("Using custom seed value: %s\r\n", argv[2]);
			GeneratePOTD((BYTE *) argv[2], strlen(argv[2]));
		}
		else
		{
			printf("Using default seed value: %s\r\n", DefaultSeed);
			GeneratePOTD((BYTE *) DefaultSeed, strlen(DefaultSeed));
		}
	}
	else if (argc > 2)
	{
		if (!strcmp(argv[1], "-D")) 
		{			
			BYTE Cleartext[64] = {0} ;
			int nCleartext = sizeof(Cleartext);
			
			BYTE EncryptedSeed[10] = {0};
			
			char * Seed = argv[2] + 2;
			
			int SeedCounter = 0;
			
			for (size_t count = 0; count < strlen(Seed) && SeedCounter <= 10; count += 2)
			{
				char temp[2] = {0};
				memcpy(temp, Seed + count, 2);
				EncryptedSeed[SeedCounter++] = strtoul(temp, NULL, 16);
			}
    
			Seed_Decryptor(EncryptedSeed, SeedCounter, Cleartext, &nCleartext);
			
			printf("Decrypted Seed: %s\r\n", Cleartext);
		}
		else if (!strcmp(argv[1], "-E"))
		{
			BYTE EncryptedSeed [64] = {0};
			int nEncryptedSeed = sizeof(EncryptedSeed);
			
			Seed_Encryptor(argv[2], strlen(argv[2]), EncryptedSeed, &nEncryptedSeed);
			
			printf("Encyrpted Seed: 0x");
			for (int i = 0; i < nEncryptedSeed; i ++)
				printf("%02X", EncryptedSeed[i]);
				
			printf("\r\n");
		}
	}
	else {
		help(argv[0]);
		return 1;
	}
	
	return 0;
	
}
