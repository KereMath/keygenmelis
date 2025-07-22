#ifndef AES_H
#define AES_H

void generate_AES128_data(int n, int method, int variation, int round);
void AES_encrypt(bit32 plaintext[], bit32 real_key[], bit32 ciphertext[], int round);

#endif
