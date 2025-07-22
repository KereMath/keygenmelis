#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <stdio.h>
#include "util.h"


int bit64buf2bin(char *str, bit64 *buf, int n) {
	bit64 *b;
	char *s;
	for (int i = 0; i < n; i++) {
		b = buf + i;
		s = str + 64 * i;
		for (int j = 0; j < 64; j++) {
			if ((*b >> j) & 0x1) 
				s[63-j] = '1';
			else
				s[63-j] = '0';
		}
	}
	
	str[n*64] = '\0';
	return 0;
}

int bit64buf2hex(char *str, bit64 *buf, int n) {
	for (int i = 0; i < n; i++) 
		sprintf(str + 16*i, "%016I64x", buf[i]);
	return 0;
}

int bia2bin64buf(bit64 *buf, BitIndexArray *bi) {
	// small index is less significant
	int k = bi->length / 64;
	for (int i=0; i<k; i++)
		buf[i] = 0x0;
	
	for (int i=0; i<bi->weight; i++) {
		int x = bi->index[i];
		int b = k - 1;
		
		while (x >= 64) {
			x -= 64;
			b--;
		}
		
		buf[b] |= ((bit64)0x0000000000000001 << x);
	}
	return 0;
}
