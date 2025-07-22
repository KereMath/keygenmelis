#include "statFunc.h"
	
vector<bool> T4_1{ false, false, false, false }; 
vector<bool> T4_2{ false, true,  false, true  }; 
vector<bool> T4_3{ false, false, true,  false }; 
vector<bool> T4_4{ false, false, false, true  }; 

vector<bool> T9_1{ true,  true,  true,  true,  true,  true,  true,  true,  true  }; 
vector<bool> T9_2{ true,  false, true,  false, true,  false, true,  false, true  }; 
vector<bool> T9_3{ true,  false, false, true,  false, false, true,  false, false }; 
vector<bool> T9_4{ true,  false, false, false, true,  false, false, false, true  }; 
vector<bool> T9_5{ true,  false, false, false, false, true,  false, false, false }; 
vector<bool> T9_6{ true,  false, false, false, false, false, true,  false, false }; 
vector<bool> T9_7{ true,  false, false, false, false, false, false, true,  false }; 
vector<bool> T9_8{ true,  false, false, false, false, false, false, false, true  }; 
vector<bool> T9_9{ true,  false, false, false, false, false, false, false, false }; 


StatFunctions KeyGeneration[] = 
{
	blk_test_fn__frequency,
	blk_test_fn__run_count,
	blk_test_fn__run_L1,
	blk_test_fn__run_L2,
	blk_test_fn__run_L3,
	blk_test_fn__run_L4,
	blk_test_fn__run_L5,
	blk_test_fn__run_ge_L5,
	blk_test_fn__template_match_4_1,
	blk_test_fn__template_match_4_2,
	blk_test_fn__template_match_4_3,
	blk_test_fn__template_match_4_4,
	blk_test_fn__linear_complexity,
	blk_test_fn__linear_complexity_profile,
	blk_test_fn__blind_spot_complexity,
	blk_test_fn__blind_spot_complexity_profile
};


ostream& operator<<(ostream& os, const vector<bool>& v) {
	int sizee = v.size();
	for (uint32_t i = 0; i < sizee; i++)
		os << v[i];
	return os; 
} 


string convert2bin(const std::vector<bool>& v) {
	string out;
	out.reserve(v.size());

	for (bool b : v) {
		out += b ? '1' : '0';
	}

	return out;
}

int binary2decimal(const string binaryRepresentation) {
	int decimalValue = stoi(binaryRepresentation, nullptr, 2);
	return decimalValue;
}

int blk_test_fn__frequency(const vector<bool> bs, const int b) {
	int count = 0;
	int sizee = bs.size();

	for (uint32_t i = 0; i < sizee; i++)
		count = count + bs[i];
	return count;
}

int blk_test_fn__run_count(const vector<bool> bs, const int b) {
	int runCount = 1;
	int sizee = bs.size();

	for (uint32_t i = 1; i < sizee; i++) {
		if (bs[i] != bs[i-1]) {
			runCount++;
		}
	}
	return runCount;
}

// controls each bit of bitset and checks whether the current run continues or ends
// depending on the run, we update the length of `longestRunLen` and counts
// the number of runs specified with the length `runLen`
int len_r_runs_test(const vector<bool> bs, const int runLen, const int gt, int *longestRunLen) {
	// if gt = 0; returns number of runs with length `runLen`
	// if gt = 1; returns number of runs with length greater than or equal to `runLen`
	
	int totalRunCount = 0, currentRunLen = 1;
	int sizee = bs.size();

	for (uint32_t i = 1; i < sizee; i++) {
		if (bs[i] != bs[i-1]) {		// Current run ends
			if (currentRunLen > (*longestRunLen))
				(*longestRunLen) = currentRunLen;
			if (gt && (currentRunLen >= runLen)) 
				totalRunCount++;
			else if (currentRunLen == runLen) 
				totalRunCount++;
			currentRunLen = 1;
		}
		else {	// Current run continues
			currentRunLen++;
		}
	}

	// Handle the final case
	if (currentRunLen > (*longestRunLen)) 
		(*longestRunLen) = currentRunLen;
	if (gt && (currentRunLen >= runLen)) 
		totalRunCount++;
	else if (currentRunLen == runLen)
		totalRunCount++;

	return totalRunCount;
}

int blk_test_fn__run_L1(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 1, 0, &longest);
}

int blk_test_fn__run_L2(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 2, 0, &longest);
}

int blk_test_fn__run_L3(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 3, 0, &longest);
}

int blk_test_fn__run_L4(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 4, 0, &longest);
}

int blk_test_fn__run_L5(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 5, 0, &longest);
}

int blk_test_fn__run_L6(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 6, 0, &longest);
}

int blk_test_fn__run_L7(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 7, 0, &longest);
}

int blk_test_fn__run_ge_L5(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 5, 1, &longest);
}

int blk_test_fn__run_ge_L8(const vector<bool> bs, const int b) {
	int longest = 0;
	return len_r_runs_test(bs, 8, 1, &longest);
}

int random_excursion_test(const vector<bool> bs, const int b) {
	int match = 0, sum = 0;
	int sizee = bs.size();

	for (uint32_t i = 0; i < sizee; i++) {
		if (bs[i])
			sum--;
		else
			sum++;
		if (sum == b) 
			match++;
	}
	return match;
}

int blk_test_fn__random_excursion_N5(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, -5);
}

int blk_test_fn__random_excursion_N4(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, -4);
}

int blk_test_fn__random_excursion_N3(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, -3);
}

int blk_test_fn__random_excursion_N2(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, -2);
}

int blk_test_fn__random_excursion_N1(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, -1);
}

int blk_test_fn__random_excursion_0(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, 0);
}

int blk_test_fn__random_excursion_1(const vector<bool> bs, const int b){
	return random_excursion_test(bs, 1);
}

int blk_test_fn__random_excursion_2(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, 2);
}

int blk_test_fn__random_excursion_3(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, 3);
}

int blk_test_fn__random_excursion_4(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, 4);
}

int blk_test_fn__random_excursion_5(const vector<bool> bs, const int b) {
	return random_excursion_test(bs, 5);
}

int blk_test_fn__random_excursion_height(const vector<bool> bs, const int b) {
	int currentHeight = 0, sum = 0;
	int sizee = bs.size();

	for (uint32_t i = 0; i < sizee; i++) {
		if (bs[i])
			sum--;
		else
			sum++;
		if (sum > currentHeight) 
			currentHeight = sum;
	}

	return currentHeight;
}

int blk_test_fn__random_excursion_depth(const vector<bool> bs, const int b) {
	int currentDepth = 0, sum = 0;
	int sizee = bs.size();

	for (uint32_t i = 0; i < sizee; i++) {
		if (bs[i])
			sum--;
		else
			sum++;
		if (sum < currentDepth) 
			currentDepth = sum;
	}

	return -currentDepth; // negative
}


// counts the number of times that given template `templatee` is found in the bitset `bs`
int explicit_template_match_test(const vector<bool> bs, const vector<bool> templatee) {
	int matchCount = 0;
	
	int size1 = bs.size();
	int size2 = templatee.size();
	for (uint32_t i = 0; i <= size1 - size2; i++) {
		int match = 1;
		for (int j = 0; j < size2; j++) {
			if (bs[i + j] != templatee[j]) {
				match = 0;
				break;
			}
		}
		if (match) 
			matchCount++;
	}

	return matchCount;
}

int blk_test_fn__template_match_4_1(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T4_1);
}

int blk_test_fn__template_match_4_2(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T4_2);
}

int blk_test_fn__template_match_4_3(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T4_3);
}

int blk_test_fn__template_match_4_4(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T4_4);
}

int blk_test_fn__template_match_9_1(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_1);
}

int blk_test_fn__template_match_9_2(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_2);
}

int blk_test_fn__template_match_9_3(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_3);
}

int blk_test_fn__template_match_9_4(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_4);
}

int blk_test_fn__template_match_9_5(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_5);
}

int blk_test_fn__template_match_9_6(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_6);
}

int blk_test_fn__template_match_9_7(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_7);
}

int blk_test_fn__template_match_9_8(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_8);
}

int blk_test_fn__template_match_9_9(const vector<bool> bs, const int b) {
	return explicit_template_match_test(bs, T9_9);
}


int blk_test_fn__disjoint_template_freq(const vector<bool> bs, const int b) {
	int numberofChunks = bs.size() / b;
	string bitsetString = convert2bin(bs);
	int binSize = pow(2, b);
	char *frequency;
	frequency = (char *)malloc(sizeof(char) * binSize);

	for (int i = 0; i < numberofChunks; i++) {
		int converted = binary2decimal(bitsetString.substr(i * b, b));
		frequency[converted] = frequency[converted] + 1;
	}

	return numberofChunks;
}


int blk_test_fn__disjoint_template_repeat(const vector<bool> bs, const int b) {
	int numberofChunks = bs.size() / b;
	string bitsetString = convert2bin(bs);
	int binSize = pow(2, b);
	char *frequency;
	frequency = (char *)malloc(sizeof(char) * binSize);

	for (int i = 0; i < numberofChunks; i++) {
		int converted = binary2decimal(bitsetString.substr(i * b, b));

		if( frequency[converted] )
			return i;
		
		else
			frequency[converted] = frequency[converted] + 1;
	}

	return -1;
}


int blk_test_fn__disjoint_template_coverage(const vector<bool> bs, const int b) {
	int numberofChunks = bs.size() / b;
	string bitsetString = convert2bin(bs);
	int binSize = pow(2, b);
	char *frequency;
	frequency = (char *)malloc(sizeof(char) * binSize);
	bool saturated = false;

	for (int i = 0; i < numberofChunks; i++) {
		int converted = binary2decimal(bitsetString.substr(i * b, b));

		if( !frequency[converted] )
			frequency[converted] = 1;

	}

	return -1;
}


int blk_test_fn__disjoint_template_saturation(const vector<bool> bs, const int b) {
	int numberofChunks = bs.size() / b;
	string bitsetString = convert2bin(bs);
	int binSize = pow(2, b);
	char *frequency;
	frequency = (char *)malloc(sizeof(char) * binSize);
	bool saturated = false;

	for (int i = 0; i < numberofChunks; i++) {
		int converted = binary2decimal(bitsetString.substr(i * b, b));

		if( !frequency[converted] )
			frequency[converted] = 1;

	}

	return -1;
}


int blk_test_fn__disjoint_template_int_max(const vector<bool> bs, const int b) {
	int numberofChunks = bs.size() / b;
	string bitsetString = convert2bin(bs);
	int max = 0;

	for (int i = 0; i < numberofChunks; i++) {
		int converted = binary2decimal(bitsetString.substr(i * b, b));
		if (converted > max)
			max = converted;
	}

	return max;
}


int blk_test_fn__disjoint_template_int_min(const vector<bool> bs, const int b) {
	int numberofChunks = bs.size() / b;
	string bitsetString = convert2bin(bs);
	int min = binary2decimal(bitsetString.substr(0, b));

	for (int i = 0; i < numberofChunks; i++) {
		int converted = binary2decimal(bitsetString.substr(i * b, b));
		if (converted < min)
			min = converted;
	}

	return min;
}


int blk_test_fn__disjoint_template_int_dif(const vector<bool> bs, const int b) {
	int max = blk_test_fn__disjoint_template_int_max(bs, b);
	int min = blk_test_fn__disjoint_template_int_min(bs, b);
	return max - min;
}


// Berlekamp-Massey algorithm for calculating linear complexity of binary sequence
// bs = byte array with binary sequence
// returns the length of LFSR with smallest length which generates bs
// for example:
// 	vector<bool> vec = {1, 0, 1, 0, 1, 1, 1, 0, 1, 0};
// 	int L = blk_test_fn_linear_complexity(vec, 5)
// 
// reference: "Handbook of Applied Cryptography", p201
int blk_test_fn__linear_complexity(const vector<bool> bs, const int blksz) {
	int N = 0, L = 0, m = -1, d, temp;

	// initialization
	vector<bool> b(blksz, false);
	vector<bool> c(blksz, false);
	vector<bool> t(blksz, false);
	vector<bool> s = bs;
	b[0] = true;	
	c[0] = true;	

	// algorithm
	while (N < blksz)
	{
		d = bs[N];
		for (int i = 1; i <= L; i++)
			d ^=  c[i] & s[N - i];				//(d+=c[i]*s[N-i] mod 2)
		
		if (d == 1) {
			t = c;						//T(D)<-C(D)
			for (int i = 0; (i + N - m) < blksz; i++) {
				temp = c[i + N - m] ^ b[i];
				c[i + N - m] = temp;
			}
			
			if (L <= (N >> 1)) {
				L = N + 1 - L;
				m = N;
				b = t;						//B(D)<-T(D)
			}
		}

		N++;
	}

	return L;
}


int blk_test_fn__linear_complexity_profile(const vector<bool> bs, const int b) {
	int t = 1, lc = 0;
	int sizee = bs.size();
	int prev = blk_test_fn__linear_complexity(bs, 1);

	for (int i = 2; i <= sizee; i++) {
		lc = blk_test_fn__linear_complexity(bs, i);

		if (lc > prev) {
			prev = lc;
			t++;
		}
	}

	return t;
}


int blk_test_fn__blind_spot_complexity(const vector<bool> bs, const int blksz) {
	if(blksz == 1)
		return bs[0];

	int x = blk_test_fn__blind_spot_complexity(bs, blksz - 1);

	if (!bs[blksz - 1]) 
		return x;

	if (x > (blksz / 2))
		return x;

	return blksz - x;
}


int blk_test_fn__blind_spot_complexity_profile(const vector<bool> bs, const int b) {
	int lc, t = 1;
	int sizee = bs.size();
	int prev = blk_test_fn__blind_spot_complexity(bs, 1);

	for (int i = 2; i <= sizee; i++) {
		lc = blk_test_fn__blind_spot_complexity(bs, i);
		
		if (lc > prev) {
			prev = lc;
			t++;
		}
	}

	return t;
}
