#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <iostream>
#include <cmath>
#include <iterator>
#include <string>
#include <sstream>
#include <fstream>
#include <ostream>
#include <bitset>
#include <vector>
#include <random>
#include <iomanip>
#include <sha.h>
#include "statFunc.h"
#include "common.h"
#include "aes.h"

using namespace std; 

typedef bool (*KGFunctions) (const vector<bool>, const double, const int);
bool blk_test_fn__template_match_4_1_helper(const vector<bool>, const double, const int);
bool blk_test_fn__template_match_4_2_helper(const vector<bool>, const double, const int);
bool blk_test_fn__template_match_4_3_helper(const vector<bool>, const double, const int);
bool blk_test_fn__template_match_4_4_helper(const vector<bool>, const double, const int);
bool blk_test_fn__linear_complexity_helper(const vector<bool>, const double, const int);
bool blk_test_fn__blind_spot_complexity_helper(const vector<bool>, const double, const int);
bool blk_test_fn__frequency_helper(const vector<bool>, const double, const int);
bool blk_test_fn__run_count_helper(const vector<bool>, const double, const int);
bool blk_test_fn__run_L1_helper(const vector<bool>, const double, const int);


vector<bool> shrinking(const vector<bool>, int);
vector<bool> alternating(const vector<bool>, int);
vector<bool> aes(const vector<bool>, int);
vector<bool> GenerateSHA256(string line);
vector<bool> urandomized();

#endif
