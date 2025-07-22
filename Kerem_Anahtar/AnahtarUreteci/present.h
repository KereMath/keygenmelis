#ifndef PRESENT_H
#define PRESENT_H

#include "common.h"

void PRESENT_key_schedule(bit64 *real_key);
bit64 PRESENT_Encrypt(bit64 Input, int round);
void generate_PRESENT_data(int n, int method, int variation, int round);

#endif
