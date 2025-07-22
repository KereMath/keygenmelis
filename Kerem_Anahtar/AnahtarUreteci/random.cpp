#include "stdafx.h"
#include "random.h"
#include <random>
#include <cstdint>

bit64 __PRNG_SEED = 0x0000000000000000;
bit64 __PRNG_VAL = 0x0000000000000000;
bool __PRNG_INITIALIZED = false; // Başlangıç durumunu izlemek için

// Rastgele sayı üretme fonksiyonu
int random(bit64 *buf, int n) {
    if (!__PRNG_INITIALIZED) {
        // Eğer başlangıç yapılmamışsa, otomatik olarak tohum değerini ayarla
        std::random_device rd; // Donanım rastgeleliği kaynağı
        std::mt19937_64 gen(rd()); // 64-bit Mersenne Twister PRNG
        std::uniform_int_distribution<bit64> dist(0, UINT64_MAX);

        __PRNG_SEED = dist(gen);
        __PRNG_VAL = __PRNG_SEED;
        __PRNG_INITIALIZED = true;
    }

    // Modern PRNG için rastgele sayı üretme
    std::random_device rd;
    std::mt19937_64 gen(rd()); // Mersenne Twister PRNG
    std::uniform_int_distribution<bit64> dist(0, UINT64_MAX);

    for (int i = 0; i < n; i++) {
        __PRNG_VAL ^= dist(gen); // Rastgelelik ekleme
        buf[i] = __PRNG_VAL;
    }

    return 0;
}

// Manuel olarak tohumlama yapmak için kullanılabilir
int seed_random(bit64 seed) {
    __PRNG_SEED = seed;
    __PRNG_VAL = seed;
    __PRNG_INITIALIZED = true;
    return 0;
}