#include "stdafx.h"
#include "plaintext.h"
#include "util.h"
#include "random.h"

#include <string.h>

#define BLOCK_SIZE 64
#define MAX_SIZE 10000

int enum_weight_iter (BitIndexArray *bi) {
	// Returns 0 if iteration success
	// // Returns 1 if iteration not possible

	if( bi->weight == 0 ) {
		bi->weight = 1;
		bi->count++;
		bi->index[0] = 0;
		
		return 0;
	}
	
	for( int i = 0; i < (bi->weight); i++ ) {
		if( i == bi->weight - 1 ){
			if( bi->index[i] == bi->length - 1 ) {
				if( bi->weight == bi->length ) 
					return 1;
				bi->weight ++;
				
				for( int j = 0; j< (bi->weight); j++) {
					bi->index[j] = j;
				}
				
				break;
			} else {
				(bi->index[i])++;
				break;
			}
		} else if( bi->index[i] + 1 < bi->index[i+1] ) {
			(bi->index[i])++;
			break;
		} else {
			bi->index[i]=i;
		}
	}
	
	bi->count++;
	return 0;
}

void gen_low(int length, int count, FILE *fp){
	char hexBuf[MAX_SIZE];
	bit64 bit64buf[MAX_SIZE];
	int indexArr[MAX_SIZE] = { 0 };
	int k = length / BLOCK_SIZE;
	BitIndexArray bi;
	bi.index = indexArr;
	bi.length = length;
	bi.weight = 0;
	bi.count = 0;
	
	bia2bin64buf(bit64buf, &bi);
	bit64buf2hex(hexBuf, bit64buf, k);
	fprintf(fp, "%s\n", hexBuf);
	
	for (;;) {
		if (enum_weight_iter(&bi) != 0) {
			printf("ERROR: Iteration ended before generating %d sequences\n", count);
		}
		
		bia2bin64buf(bit64buf, &bi);
		bit64buf2hex(hexBuf, bit64buf, k);
		fprintf(fp, "%s\n", hexBuf);
		
		if (bi.count == count) { // Success
			break;
		}
	}
}

void gen_hiw(int length, int count, FILE *fp){
	// Similar to low weight, but we take the inverse
	char hexBuf[MAX_SIZE];
	bit64 bit64buf[MAX_SIZE];
	int indexArr[MAX_SIZE] = { 0 };
	int k = length / BLOCK_SIZE;
	BitIndexArray bi;
	bi.index = indexArr;
	bi.length = length;
	bi.weight = 0;
	bi.count = 0;
	
	bia2bin64buf(bit64buf, &bi);
	for( int i = 0; i < k; i++ ) 
		bit64buf[i] = bit64buf[i] ^ (bit64) 0xFFFFFFFFFFFFFFFF; // inverse
	
	bit64buf2hex(hexBuf, bit64buf, k);
	fprintf(fp, "%s\n", hexBuf);
	
	for (;;) {
		if (enum_weight_iter(&bi) != 0) {
			printf("ERROR: Iteration ended before generating %d sequences\n", count);
		}
		
		bia2bin64buf(bit64buf, &bi);
		for (int i=0; i<k; i++) 
			bit64buf[i] = bit64buf[i] ^ (bit64) 0xFFFFFFFFFFFFFFFF; // inverse
		
		bit64buf2hex(hexBuf, bit64buf, k);
		fprintf(fp, "%s\n", hexBuf);
		
		if (bi.count == count) { // Success
			break;
		}
	}
}

void gen_bal(int length, int count, FILE *fp){
	// A balanced sequence is one with equal number of 0 and 1 bits.
	// The random number generator produces 64-bit random values.
	// Each 64-bit random number is split into two 32-bit values.
	// The right 32-bit value is replaced with the inverse of the first 32-bit value.
	// This results in a balanced 64-bit value.
	// Producing k = length/64 balanced 64-bit values yields a balanced sequence with correct length,
	// where length is a multiple of 64.
	
	bit64 rand64Buf[MAX_SIZE];
	bit32 *bit32p;
	char hexBuf[MAX_SIZE];
	int k = length / BLOCK_SIZE;
	
	for (int i = 0; i < count; i++) {
		random(rand64Buf, k);
		for (int j=0; j<k; j++) {
			bit32p = (bit32*)(rand64Buf + j);
			bit32p[1] = bit32p[0] ^ (bit32) 0xFFFFFFFF;
		}
		
		bit64buf2hex(hexBuf, rand64Buf, k);
		fprintf(fp, "%s\n", hexBuf);
		
		// NOTE: The following commented code block can be used to verify 
		// that the sequences produced are really balanced.
	
		#if 0
		char debugStr[MAX_SIZE];
		bit64buf2bin(debugStr, rand64Buf, k);
		printf("%s: ", debugStr);
		int __x = 0;
		for (int __z = 0; __z < BLOCK_SIZE * k; __z++) {
			if (debugStr[__z] == '1') __x++;
		}
		printf("%d\n", __x);
		#endif
	}
}

void gen_inc(int length, int count, FILE *fp){
	char hexBuf[MAX_SIZE];
	char padStr[MAX_SIZE];
	int k = length / BLOCK_SIZE;
	int padLen = (k-1) * BLOCK_SIZE / 4;
	memset(padStr, '0', padLen);
	padStr[padLen] = '\0';
	
	for (bit64 i=0; i<count; i++) {
		bit64buf2hex(hexBuf, &i, 1);
		fprintf(fp, "%s%s\n", padStr, hexBuf);
	}
}

void gen_rnd(int length, int count, FILE *fp){
	bit64 randBuf[MAX_SIZE];
	char hexBuf[MAX_SIZE];
	int k = length / BLOCK_SIZE;
	
	for (int i = 0; i < count; i++) {
		random(randBuf, k);
		bit64buf2hex(hexBuf, randBuf, k);
		fprintf(fp, "%s\n", hexBuf);
	}

}

#define DIFD 14
void gen_dif(int length, int count, FILE *fp) {
	// NOTE: The difference is fixed to 14.
	bit64 randBuf[MAX_SIZE];
	bit64 difBuf[MAX_SIZE];
	bit64 resBuf[MAX_SIZE];
	char hexBuf[MAX_SIZE];
	int indexArr[MAX_SIZE];
	int k = length / BLOCK_SIZE;
	
	BitIndexArray bi;
	bi.index = indexArr;
	bi.length = length;
	bi.weight = DIFD;
	bi.count = 0;

	for (int i = 0; i < DIFD; i++) 
		indexArr[i] = i; //init the BitIndexArray
	
	random(randBuf, k);
	
	for (int i = 0; i < count; i++) {
		enum_weight_iter(&bi);
		bia2bin64buf(difBuf, &bi);
		for (int j = 0; j < k; j++) 
			resBuf[j] = randBuf[j] ^ difBuf[j];
		
		bit64buf2hex(hexBuf, resBuf, k);
		fprintf(fp, "%s\n", hexBuf);
	}
}
