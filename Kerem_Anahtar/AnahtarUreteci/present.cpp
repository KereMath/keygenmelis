#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "present.h"
#include "plaintext.h"
#include "random.h"
#include <random> // C++ random kütüphanesi



///////// PRESENT Parameters /////////////////////
bit64 PRESENT_plaintext;
bit64 PRESENT_key[2];

///////// PRESENT Parameters /////////////////////
bit64 P[64] = { 0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63 };
bit64 k[33];  // PRESENT round keys
///////// PRESENT /////////////////////
void initialize_random_PRESENT_values() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<bit64> dist(0, UINT64_MAX);

    PRESENT_plaintext = dist(gen); // Rastgele plaintext üret
    for (int i = 0; i < 2; i++) {
        PRESENT_key[i] = dist(gen); // Rastgele key üret
    }
}

void PRESENT_key_schedule(bit64 *real_key) {
	bit64	i;
	bit64	key[2], temp[2], temp2 = 0;
	bit64 S[16] = { 0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2 };
	k[0] = 0xabba;
	key[0] = real_key[0];
	key[01] = real_key[1];
	for (i = 1; i < 33; i++) 	{
		temp[0] = key[0];
		temp[1] = key[1];
		k[i] = ((key[1] & 0x000000000000ffff) << 48)
			^ (key[0] >> 16);

		temp[0] = key[0] & 0x7ffff;
		key[0] >>= 19;
		key[0] ^= ((key[1] & 0xffff) << 45);
		key[1] = (temp[0] >> 3);
		key[0] ^= ((temp[0] & 0x7) << 61);

		temp2 = S[((key[1] >> 12) & 0xf)];
		key[1] = (temp2 << 12) ^ (key[1] & 0x0000000000000fff);
		key[0] ^= ((i % 32) << 15);
	}
}

bit64 getbit(bit64 Input, bit32 i) {
	Input = (Input >> i) & 0x1;
	return Input;
}

void setbit(bit64 *Input, bit32 position, bit32 value) {
	if (value)
		*Input |= (bit64)1 << position; 
	
	else
		*Input &= ~((bit64)1 << position); 
}
bit64 PRESENT_round(bit64 Input) {
	bit64 S[16] = { 0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2 };
	bit64	Output = 0, Output2 = 0;
	bit32	i;
	Output = (S[(Input >> 0) & 0xf] << 0) ^ (S[(Input >> 4) & 0xf] << 4)
		^ (S[(Input >> 8) & 0xf] << 8) ^ (S[(Input >> 12) & 0xf] << 12)
		^ (S[(Input >> 16) & 0xf] << 16) ^ (S[(Input >> 20) & 0xf] << 20)
		^ (S[(Input >> 24) & 0xf] << 24) ^ (S[(Input >> 28) & 0xf] << 28)
		^ (S[(Input >> 32) & 0xf] << 32) ^ (S[(Input >> 36) & 0xf] << 36)
		^ (S[(Input >> 40) & 0xf] << 40) ^ (S[(Input >> 44) & 0xf] << 44)
		^ (S[(Input >> 48) & 0xf] << 48) ^ (S[(Input >> 52) & 0xf] << 52)
		^ (S[(Input >> 56) & 0xf] << 56) ^ (S[(Input >> 60) & 0xf] << 60);

	for (i = 0; i < 64; i++)
		setbit(&Output2, i, getbit(Output, P[i])); 
	
	return Output2;
}

bit64 PRESENT_Encrypt(bit64 Input, int round) {
	for (int i = 1; i < round; i++)	{
		Input ^= k[i];
		Input = PRESENT_round(Input);
		//		printf("Round Output %2d: %016I64x\n", i, Input);
	}

	Input ^= k[32]; // Omitted since it does not change the output difference
	return Input;
}

void PRESENT_write_to_file(FILE *fp, bit64 output) {
	for (int j = 0; j < 64; j++) {
		if ((output >> j) & 0x1) 
			fprintf(fp, "1");
		else 
			fprintf(fp, "0");
	}

	fprintf(fp, "\n");
}

void generate_PRESENT_data(int n, int method, int variation, int round) {
	initialize_random_PRESENT_values(); // Rastgele key ve plaintext oluştur

	char str[30000];
	char temp[30000];
	bit64 key[2], temp2[2], temp3;
	bit64 plaintext, ciphertext, t;
	FILE *fp= NULL, *fp2=NULL;
	char methodname[64];
	plaintext = PRESENT_plaintext;
	for (int i=0; i<2; i++) 
		key[i] = PRESENT_key[i];
	
	switch(method) {
		case 1:
			sprintf(methodname, "incremental");
			break;
		case 2: 
			sprintf(methodname, "CPC");
			break;
		case 3:
			sprintf(methodname, "low");
			break;
		case 4:
			sprintf(methodname, "high");
			break;
		case 5:
			sprintf(methodname, "balanced");
			break;
		case 6:
			sprintf(methodname, "random");
			break;
		case 7:
			sprintf(methodname, "14dif");
			break;
		case 8:
			sprintf(methodname, "rPrKxP");
			break;
		case 9:
			sprintf(methodname, "rPrKxK");
			break;
		case 10:
			sprintf(methodname, "rPrKxPxK");
			break;
		default:
			return;
	}
	
	PRESENT_key_schedule(key);
	char inname[128], outname[128];
	if (method < 8)
		sprintf(outname, "PRESENT-%s-%d.txt", methodname, variation);
	else
		sprintf(outname, "PRESENT-%s.txt", methodname);
	
	fp2 = fopen(outname, "w");
	if (method != 2 && method < 8) { // CBC does not use input file
		sprintf(inname, "PRESENT-%s-plaintext.txt", methodname);
		fp = fopen(inname, "w");
		switch (method) {
			case 1:
				gen_inc (64, n, fp);
				break;
			case 3:
				gen_low (64, n, fp);
				break;
			case 4:
				gen_hiw (64, n, fp);
				break;
			case 5:
				gen_bal (64, n, fp);
				break;
			case 6:
				gen_rnd (64, n, fp);
				break;
			case 7:
				gen_dif(64, n, fp);
				break;
		}
		
		fclose (fp);
		fp = fopen(inname, "r");
	}
	
	for (int i=0; i<n; i++) {
		if (method == 2) { // CPC
			if (i > 0) 
				plaintext = ciphertext;
		}
		
		else if (method >= 8) {
			random(&plaintext, 1);
			random(key, 2);
			PRESENT_key_schedule(key);
		}
		
		else { // scan and parse input from file
			#ifdef WIN32
			fscanf_s(fp, "%s", str);
			// plaintext = (bit64)strtoul(str, NULL, 16);
			for (int j = 0; j<2; j++) {
				strncpy_s(temp, str + 8 * j, 8);
				temp[8] = '\0';
				temp2[j] = (bit32)strtoul(temp, NULL, 16); // strtould Visual studio'da hep 32-bit de�er d�nd�rd��� i�in iki a�amada i�lem yapmak gerekiyor
			}
			
			plaintext = (temp2[0]<<32) | temp2[1];
			
			#else
			fscanf(fp, "%s", str);
			plaintext = (bit64)strtoul(str, NULL, 16);
			#endif
		}
		
		if (method >= 8) {
			ciphertext = PRESENT_Encrypt(plaintext, round + 1);
			
			if (method == 8) {
				t = ciphertext ^ plaintext;
			}
			else if (method == 9) {
				t = ciphertext ^ key[0];
			}
			else if (method == 10) {
				t = ciphertext ^ plaintext ^ key[0];
			}
			PRESENT_write_to_file(fp2, t);
		} 
		else {
			if (variation == 1 || variation == 2) 
				ciphertext = PRESENT_Encrypt(plaintext, round + 1);
			
			else if (variation == 3 || variation == 4) {
				temp3 = plaintext;
				plaintext = key[0];
				key[0] = temp3;
				PRESENT_key_schedule(key);
				ciphertext = PRESENT_Encrypt(plaintext, round + 1);
			}
			
			if (variation == 1 || variation == 3)
				PRESENT_write_to_file(fp2, ciphertext);
			 
			else if (variation == 2 || variation == 4) {
				t = ciphertext ^ plaintext;
				PRESENT_write_to_file(fp2, t);
			}
		}
	}
	
	if (method != 2 && method < 8) {
		fclose(fp);
		remove(inname);
	}
	
	fclose (fp2);
}
