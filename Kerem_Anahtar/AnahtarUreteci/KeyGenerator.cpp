#include "stdafx.h"
#include "KeyGenerator.h"
#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <bitset>
#include <chrono>

bool blk_test_fn__frequency_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__frequency(bs, size);

	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result > 45) && (result < 83);
			else
				return (result > 48) && (result < 80);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result > 100) && (result < 153);
			else
				return (result > 105) && (result < 151);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result > 218) && (result < 294);
			else
				return (result > 224) && (result < 288);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result > 459) && (result < 566);
			else
				return (result > 468) && (result < 557);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result > 950) && (result < 1100);
			else
				return (result > 961) && (result < 1087);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result > 1943) && (result < 2154);
			else
				return (result > 1959) && (result < 2137);
			break;
	}
	return true;
}

bool blk_test_fn__run_count_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__run_count(bs, size);
	
	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result > 46) && (result < 86);
			else
				return (result > 48) && (result < 80);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result > 102) && (result < 155);
			else
				return (result > 106) && (result < 151);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result > 219) && (result < 296);
			else
				return (result > 224) && (result < 288);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result > 460) && (result < 566);
			else
				return (result > 468) && (result < 557);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result > 950) && (result < 1098);
			else
				return (result > 961) && (result < 1088);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result > 1943) && (result < 2150);
			else
				return (result > 1959) && (result < 2137);
			break;
	}
	return true;
}

bool blk_test_fn__run_L1_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__run_L1(bs, size);
	
	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result > 13) && (result < 60);
			else
				return (result > 16) && (result < 51);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result > 37) && (result < 96);
			else
				return (result > 41) && (result < 91);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result > 89) && (result < 175);
			else
				return (result > 94) && (result < 165);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result > 200) && (result < 319);
			else
				return (result > 208) && (result < 307);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result > 431) && (result < 599);
			else
				return (result > 443) && (result < 584);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result > 909) && (result < 1143);
			else
				return (result > 927) && (result < 1123);
			break;
	}
	return true;
}

bool blk_test_fn__template_match_4_1_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__template_match_4_1(bs, size);
	
	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result < 25);
			else
				return (result < 22);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result < 38);
			else
				return (result < 34);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result < 63);
			else
				return (result < 56);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result < 105);
			else
				return (result < 97);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result < 185);
			else
				return (result < 174);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result < 334);
			else
				return (result < 320);
			break;
	}
	return true;
}

bool blk_test_fn__template_match_4_2_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__template_match_4_2(bs, size);
	
	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result < 19);
			else
				return (result < 17);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result < 30);
			else
				return (result < 27);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result < 51);
			else
				return (result < 48);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result < 91);
			else
				return (result < 86);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result < 165);
			else
				return (result < 158);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result < 308);
			else
				return (result < 298);
			break;
	}
	return true;
}

bool blk_test_fn__template_match_4_3_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__template_match_4_3(bs, size);
	
	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result < 16);
			else
				return (result < 15);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result < 28);
			else
				return (result < 26);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result < 48);
			else
				return (result < 46);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result < 87);
			else
				return (result < 83);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result < 160);
			else
				return (result < 154);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result < 301);
			else
				return (result < 293);
			break;
	}
	return true;
}

bool blk_test_fn__template_match_4_4_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__template_match_4_4(bs, size);
	
	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result < 15);
			else
				return (result < 14);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result < 26);
			else
				return (result < 24);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result < 45);
			else
				return (result < 43);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result < 82);
			else
				return (result < 79);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result < 154);
			else
				return (result < 149);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result < 293);
			else
				return (result < 286);
			break;
	}
	return true;
}

bool blk_test_fn__linear_complexity_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__linear_complexity(bs, size);
	
	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result > 59) && (result < 67);
			else
				return (result > 60) && (result < 68);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result > 123) && (result < 134);
			else
				return (result > 123) && (result < 132);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result > 251) && (result < 262);
			else
				return (result > 251) && (result < 262);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result > 507) && (result < 518);
			else
				return (result > 508) && (result < 517);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result > 1019) && (result < 1030);
			else
				return (result > 1020) && (result < 1029);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result > 2043) && (result < 2054);
			else
				return (result > 2044) && (result < 2053);
			break;
	}
	return true;
}

bool blk_test_fn__blind_spot_complexity_helper(const vector<bool> bs, const double linComplexity, const int size) {
	int result = blk_test_fn__blind_spot_complexity(bs, size);
	
	switch(size){
		case 128:
			if(linComplexity == 0.01)
				return (result > 59) && (result < 70);
			else
				return (result > 60) && (result < 68);
			break;
		case 256:
			if(linComplexity == 0.01)
				return (result > 123) && (result < 134);
			else
				return (result > 123) && (result < 132);
			break;
		case 512:
			if(linComplexity == 0.01)
				return (result > 251) && (result < 262);
			else
				return (result > 251) && (result < 262);
			break;
		case 1024:
			if(linComplexity == 0.01)
				return (result > 507) && (result < 518);
			else
				return (result > 508) && (result < 517);
			break;
		case 2048:
			if(linComplexity == 0.01)
				return (result > 1019) && (result < 1030);
			else
				return (result > 1020) && (result < 1029);
			break;
		case 4096:
			if(linComplexity == 0.01)
				return (result > 2043) && (result < 2054);
			else
				return (result > 2044) && (result < 2053);
			break;
	}
	return true;
}

vector<bool> aes(const vector<bool> seed, int outputsize) {
	vector<bool> result2;
	int repetition = outputsize / 128;

	bit32 plaintext[4];
	bit32 ciphertext[4];
	bit32 key[4];
		
	for(int i = 0; i < 4; i++) {
		stringstream ss;
		for(int j = 0; j < 32; j++){ 
			ss << seed[8*i + j];
			bit32 value = stoull(ss.str(), 0, 2);
			plaintext[i] = value;
		}
	}
	
	for(int i = 4; i < 8; i++) {
		stringstream ss;
		for(int j = 0; j < 32; j++){ 
			ss << seed[8*i + j];
			bit32 value = stoull(ss.str(), 0, 2);
			key[i-4] = value;
		}
	}

	AES_encrypt(plaintext, key, ciphertext, 10);
	for(int i = 0; i < 4; i++) {
		bitset<32> bs(ciphertext[i]);
		for(int j = 0; j < 32; j++)
			result2.push_back(bs[31-j]);
	}
	
	for(int count = 1; count < repetition; count++) {
		AES_encrypt(ciphertext, key, ciphertext, 10);
		for(int i = 0; i < 4; i++) {
			bitset<32> bs(ciphertext[i]);
			for(int j = 0; j < 32; j++)
				result2.push_back(bs[31-j]);
		}
	}
	
	return result2;
}

vector<bool> shrinking(vector<bool> seed, int outputSize) {
    // LFSR başlangıç durumlarını belirle
    vector<bool> lfsr1(seed.begin(), seed.begin() + 127); // Daha uzun LFSR
    vector<bool> lfsr2(seed.begin() + 127, seed.end());
    vector<bool> output;

    for (int i = 0; i < outputSize;) {
        // İlk LFSR'nin son biti '1' ise ikinci LFSR'nin son bitini seç
        if (lfsr1.back()) {
            output.push_back(lfsr2.back());
            i++;
        }

        // Daha karmaşık geri besleme polinomları
        unsigned char bit1 = lfsr1[0] ^ lfsr1[31] ^ lfsr1[63] ^ lfsr1[95] ^ lfsr1[126];
        unsigned char bit2 = lfsr2[0] ^ lfsr2[29] ^ lfsr2[59] ^ lfsr2[89] ^ lfsr2[125];

        // LFSR'leri güncelle
        lfsr1.insert(lfsr1.begin(), bit1);
        lfsr1.pop_back();
        lfsr2.insert(lfsr2.begin(), bit2);
        lfsr2.pop_back();
    }

    return output;
}

vector<bool> alternating(const vector<bool> seed, int outputSize) {
    vector<bool> lfsr1(seed.begin(), seed.begin() + 71);
    vector<bool> lfsr2(seed.begin() + 71, seed.begin() + 154);
    vector<bool> lfsr3(seed.begin() + 154, seed.begin() + 255);
    vector<bool> output;

    for (int i = 0; i < outputSize; i++) {
        if (lfsr1.back())
            output.push_back(lfsr2.back());
        else
            output.push_back(lfsr3.back());

        unsigned char bit1 = lfsr1[70] ^ lfsr1[67] ^ lfsr1[66] ^ lfsr1[65];
        unsigned char bit2 = lfsr2[82] ^ lfsr2[78] ^ lfsr2[69] ^ lfsr2[67];
        unsigned char bit3 = lfsr3[100] ^ lfsr3[97] ^ lfsr3[95] ^ lfsr3[94];

        lfsr1.insert(lfsr1.begin(), bit1);
        lfsr1.pop_back();
        lfsr2.insert(lfsr2.begin(), bit2);
        lfsr2.pop_back();
        lfsr3.insert(lfsr3.begin(), bit3);
        lfsr3.pop_back();
    }

    return output;
}
const char* hex_char_to_bin(char c)
{
	switch(toupper(c))
	{
		case '0': return "0000";
		case '1': return "0001";
		case '2': return "0010";
		case '3': return "0011";
		case '4': return "0100";
		case '5': return "0101";
		case '6': return "0110";
		case '7': return "0111";
		case '8': return "1000";
		case '9': return "1001";
		case 'A': return "1010";
		case 'a': return "1010";
		case 'B': return "1011";
		case 'b': return "1011";
		case 'C': return "1100";
		case 'c': return "1100";
		case 'D': return "1101";
		case 'd': return "1101";
		case 'E': return "1110";
		case 'e': return "1110";
		case 'F': return "1111";
		case 'f': return "1111";
	}
}


string to_hex(unsigned char s) {
	stringstream ss;
	ss << hex << (int) s;
	return ss.str();
}  


string hex_str_to_bin_str(const std::string& hex) {
	string bin;
	for(unsigned i = 0; i != hex.length(); ++i)
		bin += hex_char_to_bin(hex[i]);
	return bin;
}


vector<bool> GenerateSHA256(string line) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, line.c_str(), line.length());
	SHA256_Final(hash, &sha256);
	
	string output = "";
	for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		output += to_hex(hash[i]);
	}
	
	string bin1 = hex_str_to_bin_str(output);
	vector<bool> bin2;
	for(auto a : bin1)
		bin2.push_back(a == '1');

	return bin2;
}



std::vector<bool> urandomized() {
    std::vector<uint8_t> randomBytes(32);

    // Use std::random_device for cryptographic randomness
    std::random_device rd;

    // Fill the randomBytes vector with random values
    for (auto &byte : randomBytes) {
        byte = rd(); // Random device generates a byte
    }

    // Convert to hexadecimal string
    std::ostringstream ss;
    for (auto byte : randomBytes) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned>(byte);
    }
    std::string outputString = ss.str();

    // Convert to binary string
    std::string binString = hex_str_to_bin_str(outputString);

    // Convert to vector<bool>
    std::vector<bool> binaryVector;
    for (char c : binString) {
        binaryVector.push_back(c == '1');
    }

    return binaryVector;
}