#ifndef PLAINTEXT_H
#define PLAINTEXT_H

#include <stdio.h>

void gen_low(int length, int count, FILE *fp);
void gen_hiw(int length, int count, FILE *fp);
void gen_bal(int length, int count, FILE *fp);
void gen_inc(int length, int count, FILE *fp);
void gen_rnd(int length, int count, FILE *fp);
void gen_dif(int length, int count, FILE *fp);

#endif
