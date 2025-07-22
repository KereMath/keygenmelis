#ifndef UTIL_H
#define UTIL_H

#include "common.h"

typedef struct {
	int *index; /* Array of bit indices */
	int count;
	int weight;
	int length;
} BitIndexArray;

int bit64buf2bin(char *str, bit64 *buf, int n);
int bit64buf2hex(char *str, bit64 *buf, int n);
int bia2bin64buf(bit64 *buf, BitIndexArray *bi);

#endif
