#ifndef RANDOM_H
#define RANDOM_H

#include "present.h"

int seed_random(bit64 seed);
int random(bit64 *buf, int n);

#endif
