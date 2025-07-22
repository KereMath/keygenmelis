#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
using namespace OpenXLSX;

	
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


ostream& operator<<(ostream& os, const vector<bool>& v) {
	size_t N = v.size();
	for (uint32_t i = 0; i < N; i++)
		os << v[i];
	return os; 
} 

size_t binary2decimal(const vector<bool> &bs, size_t start, size_t length) {
	size_t decimalValue = 0;
	
	for(int Index = 0; Index < length; Index++)
	{
		//result |= boolsSegment.Array[boolsSegment.Offset + Index] ? 1 : 0;
		decimalValue |= (uint8_t) bs[start + Index];
		decimalValue <<= 1;
	}
	return decimalValue >> 1;
}

size_t blk_test_fn__frequency(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t count = 0;

	for (size_t i = 0; i < N; i++)
		count = count + bs[i];
	return count;
}

size_t blk_test_fn__run_count(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t runCount = 1;

	for (size_t i = 1; i < N; i++) {
		if (bs[i] != bs[i-1]) {
			runCount++;
		}
	}
	return runCount;
}

// controls each bit of bitset and checks whether the current run continues or ends
// depending on the run, we update the length of `longestRunLen` and counts
// the number of runs specified with the length `runLen`
size_t len_r_runs_test(const vector<bool> &bs, const size_t N, const size_t runLen, const size_t gt, size_t *longestRunLen) {
	// if gt = 0; returns number of runs with length `runLen`
	// if gt = 1; returns number of runs with length greater than or equal to `runLen`
	
	size_t totalRunCount = 0, currentRunLen = 1;

	for (size_t i = 1; i < N; i++) {
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

size_t blk_test_fn__run_L1(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 1, 0, &longest);
}

size_t blk_test_fn__run_L2(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 2, 0, &longest);
}

size_t blk_test_fn__run_L3(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 3, 0, &longest);
}

size_t blk_test_fn__run_L4(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 4, 0, &longest);
}

size_t blk_test_fn__run_L5(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 5, 0, &longest);
}

size_t blk_test_fn__run_L6(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 6, 0, &longest);
}

size_t blk_test_fn__run_L7(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 7, 0, &longest);
}

size_t blk_test_fn__run_ge_L5(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 5, 1, &longest);
}

size_t blk_test_fn__run_ge_L8(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t longest = 0;
	return len_r_runs_test(bs, N, 8, 1, &longest);
}

size_t random_excursion_test(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t match = 0, sum = 0;

	for (uint32_t i = 0; i < N; i++) {
		if (bs[i])
			sum--;
		else
			sum++;
		if (sum == b) 
			match++;
	}
	return match;
}

size_t blk_test_fn__random_excursion_N5(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, -5);
}

size_t blk_test_fn__random_excursion_N4(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, -4);
}

size_t blk_test_fn__random_excursion_N3(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, -3);
}

size_t blk_test_fn__random_excursion_N2(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, -2);
}

size_t blk_test_fn__random_excursion_N1(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, -1);
}

size_t blk_test_fn__random_excursion_0(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, 0);
}

size_t blk_test_fn__random_excursion_1(const vector<bool> &bs, const size_t N, const size_t b){
	return random_excursion_test(bs, N, 1);
}

size_t blk_test_fn__random_excursion_2(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, 2);
}

size_t blk_test_fn__random_excursion_3(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, 3);
}

size_t blk_test_fn__random_excursion_4(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, 4);
}

size_t blk_test_fn__random_excursion_5(const vector<bool> &bs, const size_t N, const size_t b) {
	return random_excursion_test(bs, N, 5);
}

size_t blk_test_fn__random_excursion_height(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t currentHeight = 0, sum = 0;

	for (uint32_t i = 0; i < N; i++) {
		if (bs[i])
			sum--;
		else
			sum++;
		if (sum > currentHeight) 
			currentHeight = sum;
	}

	return currentHeight;
}

size_t blk_test_fn__random_excursion_depth(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t currentDepth = 0, sum = 0;

	for (uint32_t i = 0; i < N; i++) {
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
size_t explicit_template_match_test(const vector<bool> &bs, const size_t N, const vector<bool> templatee) {
	size_t matchCount = 0;
	
	size_t size2 = templatee.size();
	for (uint32_t i = 0; i <= N - size2; i++) {
		size_t match = 1;
		for (size_t j = 0; j < size2; j++) {
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

size_t blk_test_fn__template_match_4_1(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T4_1);
}

size_t blk_test_fn__template_match_4_2(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T4_2);
}

size_t blk_test_fn__template_match_4_3(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T4_3);
}

size_t blk_test_fn__template_match_4_4(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T4_4);
}

size_t blk_test_fn__template_match_9_1(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_1);
}

size_t blk_test_fn__template_match_9_2(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_2);
}

size_t blk_test_fn__template_match_9_3(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_3);
}

size_t blk_test_fn__template_match_9_4(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_4);
}

size_t blk_test_fn__template_match_9_5(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_5);
}

size_t blk_test_fn__template_match_9_6(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_6);
}

size_t blk_test_fn__template_match_9_7(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_7);
}

size_t blk_test_fn__template_match_9_8(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_8);
}

size_t blk_test_fn__template_match_9_9(const vector<bool> &bs, const size_t N, const size_t b) {
	return explicit_template_match_test(bs, N, T9_9);
}


size_t blk_test_fn__disjoint_template_freq(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t numberofChunks = N / b;
	vector<bool> templatee(b, false);
	templatee[b-1] = true;
	size_t result = 0;

	size_t templateVal = binary2decimal(templatee, 0, b);

	for (size_t i = 0; i < numberofChunks; i++) {
		size_t converted = binary2decimal(bs, i * b, b);
		if( converted == templateVal )
			result++;
	}

	return result;
}


size_t blk_test_fn__disjoint_template_repeat(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t numberofChunks = N / b, c = 0;
	size_t binSize = pow(2, b);
    	vector<size_t> seen(binSize, 0);
    	size_t covered = 0;
    
	for (size_t i = 0; i < numberofChunks; i++) {
		size_t current = binary2decimal(bs, i * b, b);
        	if( seen[current] == 0 ) {
            		seen[current] = 1;
            		covered++;
        	}
		else
			return i + 1;
	}

	return numberofChunks;
}


size_t blk_test_fn__disjoint_template_coverage(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t numberofChunks = N / b;
	size_t binSize = pow(2, b);
	vector<size_t> seen(binSize, 0);
	size_t covered = 0;
    
	for (size_t i = 0; i < numberofChunks; i++) {
		size_t current = binary2decimal(bs, i * b, b);
        if( seen[current] == 0 ) {
			seen[current] = 1;
			covered++;
        }
	}

	return covered;
}


size_t blk_test_fn__disjoint_template_saturation(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t numberofChunks = N / b;
	size_t binSize = pow(2, b);
    vector<size_t> seen(binSize, 0);
	size_t current = 0, total = 0;

	for (size_t i = 0; i < numberofChunks; i++) {
		total = 0;
		current = binary2decimal(bs, i * b, b);
	
		if( seen[current] == 0 )
			seen[current] = 1;
		for (size_t j = 0; j < binSize; j++) {
			total = total + seen[j];
			if (total == binSize)
				return i;
		}
	}

	return numberofChunks;
}

size_t blk_test_fn__disjoint_template_int_max(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t numberofChunks = N / b;
	size_t max = 0;

	for (size_t i = 0; i < numberofChunks; i++) {
		size_t converted = binary2decimal(bs, i * b, b);
		if (converted > max)
			max = converted;
	}

	return max;
}


size_t blk_test_fn__disjoint_template_int_min(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t numberofChunks = N / b;
	size_t min = binary2decimal(bs, 0, b);

	for (size_t i = 0; i < numberofChunks; i++) {
		size_t converted = binary2decimal(bs, i * b, b);
		if (converted < min)
			min = converted;
	}

	return min;
}


size_t blk_test_fn__disjoint_template_int_dif(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t max = blk_test_fn__disjoint_template_int_max(bs, N, b);
	size_t min = blk_test_fn__disjoint_template_int_min(bs, N, b);
	return max - min;
}


// Berlekamp-Massey algorithm for calculating linear complexity of binary sequence
// bs = byte array with binary sequence
// returns the length of LFSR with smallest length which generates bs
// for example:
// 	vector<bool> vec = {1, 0, 1, 0, 1, 1, 1, 0, 1, 0};
// 	size_t L = blk_test_fn_linear_complexity(vec, 5)
// 
// reference: "Handbook of Applied Cryptography", p201
size_t blk_test_fn__linear_complexity(const vector<bool> &bs, const size_t blksz, const size_t bb) {
	size_t N = 0, L = 0, m = -1, d, temp;

	// initialization
	vector<bool> b(4096, false);
	vector<bool> c(4096, false);
	vector<bool> t(4096, false);
	vector<bool> s = bs;
	b[0] = true;	
	c[0] = true;	

	// algorithm
	while (N < blksz)
	{
		d = bs[N];
		for (size_t i = 1; i <= L; i++)
			d ^=  c[i] & s[N - i];				//(d+=c[i]*s[N-i] mod 2)
		
		if (d == 1) {
			t = c;						//T(D)<-C(D)
			for (size_t i = 0; (i + N - m) < blksz; i++) {
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


size_t blk_test_fn__linear_complexity_profile(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t t = 1, lc = 0;
	size_t prev = blk_test_fn__linear_complexity(bs, 1, 0);

	for (size_t i = 2; i <= N; i++) {
		lc = blk_test_fn__linear_complexity(bs, i, 0);

		if (lc > prev) {
			prev = lc;
			t++;
		}
	}

	return t;
}


size_t blk_test_fn__blind_spot_complexity(const vector<bool> &bs, const size_t N, const size_t b) {
	if(N == 1){
		if( bs[0] )
			return 1;
		return 0;
	}

	size_t x = blk_test_fn__blind_spot_complexity(bs, N - 1, b);

	if (!bs[N - 1]) 
		return x;

	if (x > (N / 2))
		return x;

	return N - x;
}


size_t blk_test_fn__blind_spot_complexity_profile(const vector<bool> &bs, const size_t N, const size_t b) {
	size_t lc, t = 1;
	size_t prev = blk_test_fn__blind_spot_complexity(bs, 1, 0);

	for (size_t i = 2; i <= N; i++) {
		lc = blk_test_fn__blind_spot_complexity(bs, i, 0);
		
		if (lc > prev) {
			prev = lc;
			t++;
		}
	}

	return t;
}


/*
size_t main() 
{ 
	ifstream inFile;
	inFile.open("input45.txt");
	string x;
	inFile >> x;
	// cout << x << endl;

	// cout << blk_test_fn__frequency(bitset2) << endl;
	// cout << blk_test_fn__run_count(bitset2) << endl;
	// cout << random_excursion_test(bitset2, 3) << endl;
	// cout << blk_test_fn__random_excursion_height(bitset2) << endl;
	// cout << blk_test_fn__random_excursion_depth(bitset2) << endl;

		
	// cout << "template match 4 bits" << endl;
	// cout << blk_test_fn__template_match_4_1(bitsett) << endl;
	// cout << blk_test_fn__template_match_4_2(bitsett) << endl;
	// cout << blk_test_fn__template_match_4_3(bitsett) << endl;
	// cout << blk_test_fn__template_match_4_4(bitsett) << endl;
	
	// cout << "template match 9 bits" << endl;
	// cout << blk_test_fn__template_match_9_1(bitsett) << endl;
	// cout << blk_test_fn__template_match_9_2(bitsett) << endl;
	// cout << blk_test_fn__template_match_9_3(bitsett) << endl;
	// cout << blk_test_fn__template_match_9_4(bitsett) << endl;
	// cout << blk_test_fn__template_match_9_5(bitsett) << endl;
	// cout << blk_test_fn__template_match_9_6(bitsett) << endl;
	// cout << blk_test_fn__template_match_9_7(bitsett) << endl;
	// cout << blk_test_fn__template_match_9_8(bitsett) << endl;
	// cout << blk_test_fn__template_match_9_9(bitsett) << endl;
	
	
	// cout << "run tests for: " << bitsett << endl;
	// size_t longest = 0;
	// len_r_runs_test(bitsett, 1, 0, &longest);
	// cout << "Longest Run : " << longest << endl;
	// cout << blk_test_fn__run_L1(bitsett) << endl;
	// cout << blk_test_fn__run_L2(bitsett) << endl;
	// cout << blk_test_fn__run_L3(bitsett) << endl;
	// cout << blk_test_fn__run_L4(bitsett) << endl;
	// cout << blk_test_fn__run_L5(bitsett) << endl;

	// cout << "size_t max" << endl;
	// cout << bitset3 << endl;
	// cout << blk_test_fn__disjoint_template_int_max(bitset3, 5) << endl;
	// cout << blk_test_fn__disjoint_template_int_min(bitset3, 5) << endl;
	
	// cout << "linear complexity " << endl;
	// bitset<26> bitset44("10100111110100110000111111");
	// cout << blk_test_fn__linear_complexity(bitset44) << endl;
	

	// cout << blk_test_fn__linear_complexity(bitsett) << endl;
	// cout << blk_test_fn__disjoint_template_repeat(bitset45, 3) << endl;

	
	//inFile.close();
	
	vector<bool> deneme;
	deneme.push_back(true);
	deneme.push_back(true);
	deneme.push_back(false);
	deneme.push_back(true);
	deneme.push_back(true);
	deneme.push_back(true);
	deneme.push_back(true);
	deneme.push_back(false);
	deneme.push_back(false);
	deneme.push_back(false);
	deneme.push_back(false);
	deneme.push_back(false);
	
	cout << deneme << endl;
	



	// vector<bool> ls = {0, 1, 1, 1, 0, 0, 1, 0, 1, 1};
	// cout << "lin comp: " << blk_test_fn__linear_complexity(ls, 10) << endl;
	return 0; 
}
*/


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
				return (result > 1019) && (result < 1023);
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
int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "input.txt dosyası açılamadı!" << endl;
        return 1;
    }

    // Excel dosyasını oluştur
    XLDocument doc;
    doc.create("output.xlsx");
    auto wks = doc.workbook().addWorksheet("Sonuçlar");

    // Başlıkları yaz
    wks.cell(XLCellReference("A1")).value() = "Anahtar";
    wks.cell(XLCellReference("B1")).value() = "Boyut";
    wks.cell(XLCellReference("C1")).value() = "Frequency Test";
    wks.cell(XLCellReference("D1")).value() = "Run Count Test";
    wks.cell(XLCellReference("E1")).value() = "Run L1 Test";
    wks.cell(XLCellReference("F1")).value() = "Template Match 4-1";
    wks.cell(XLCellReference("G1")).value() = "Template Match 4-2";
    wks.cell(XLCellReference("H1")).value() = "Template Match 4-3";
    wks.cell(XLCellReference("I1")).value() = "Template Match 4-4";
    wks.cell(XLCellReference("J1")).value() = "Linear Complexity";
    wks.cell(XLCellReference("K1")).value() = "Blind Spot Complexity";

    string line;
    int row = 2; // Satır 2'den başla (başlıklar 1. satır)
    
    while (getline(inputFile, line)) {
        vector<bool> bits = convert_to_bool_vector(line);
        int size = bits.size();
        double linComplexity = 0.01; // Varsayılan değer

        // Testleri gerçekleştir
        bool freq_result = blk_test_fn__frequency_helper(bits, linComplexity, size);
        bool run_count_result = blk_test_fn__run_count_helper(bits, linComplexity, size);
        bool run_l1_result = blk_test_fn__run_L1_helper(bits, linComplexity, size);
        bool temp_match_4_1_result = blk_test_fn__template_match_4_1_helper(bits, linComplexity, size);
        bool temp_match_4_2_result = blk_test_fn__template_match_4_2_helper(bits, linComplexity, size);
        bool temp_match_4_3_result = blk_test_fn__template_match_4_3_helper(bits, linComplexity, size);
        bool temp_match_4_4_result = blk_test_fn__template_match_4_4_helper(bits, linComplexity, size);
        bool linear_complexity_result = blk_test_fn__linear_complexity_helper(bits, linComplexity, size);
        bool blind_spot_complexity_result = blk_test_fn__blind_spot_complexity_helper(bits, linComplexity, size);

        // Sonuçları Excel'e yaz
        wks.cell(XLCellReference(row, 1)).value() = line;
        wks.cell(XLCellReference(row, 2)).value() = size;
        wks.cell(XLCellReference(row, 3)).value() = evaluate_test_result(freq_result);
        wks.cell(XLCellReference(row, 4)).value() = evaluate_test_result(run_count_result);
        wks.cell(XLCellReference(row, 5)).value() = evaluate_test_result(run_l1_result);
        wks.cell(XLCellReference(row, 6)).value() = evaluate_test_result(temp_match_4_1_result);
        wks.cell(XLCellReference(row, 7)).value() = evaluate_test_result(temp_match_4_2_result);
        wks.cell(XLCellReference(row, 8)).value() = evaluate_test_result(temp_match_4_3_result);
        wks.cell(XLCellReference(row, 9)).value() = evaluate_test_result(temp_match_4_4_result);
        wks.cell(XLCellReference(row, 10)).value() = evaluate_test_result(linear_complexity_result);
        wks.cell(XLCellReference(row, 11)).value() = evaluate_test_result(blind_spot_complexity_result);

        row++;
    }

    // Excel dosyasını kaydet ve kapat
    doc.save();
    inputFile.close();

    cout << "İşlem tamamlandı. 'output.xlsx' dosyasını kontrol ediniz." << endl;
    return 0;
}