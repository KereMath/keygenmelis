#ifndef STATFUNC_H
#define STATFUNC_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

typedef int (*StatFunctions) (const vector<bool> bs, const int b);

ostream& operator<<(ostream& os, const vector<bool>& v); 

string convert2bin(const std::vector<bool>& v);

int binary2decimal(const string binaryRepresentation);

int blk_test_fn__frequency(const vector<bool> bs, const int b);

int blk_test_fn__run_count(const vector<bool> bs, const int b);

int len_r_runs_test(const vector<bool> bs, const int runLen, const int gt, int *longestRunLen);

int blk_test_fn__run_L1(const vector<bool> bs, const int b);

int blk_test_fn__run_L2(const vector<bool> bs, const int b);

int blk_test_fn__run_L3(const vector<bool> bs, const int b);

int blk_test_fn__run_L4(const vector<bool> bs, const int b);

int blk_test_fn__run_L5(const vector<bool> bs, const int b);

int blk_test_fn__run_L6(const vector<bool> bs, const int b);

int blk_test_fn__run_L7(const vector<bool> bs, const int b);

int blk_test_fn__run_ge_L5(const vector<bool> bs, const int b);

int blk_test_fn__run_ge_L8(const vector<bool> bs, const int b);

int random_excursion_test(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_N5(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_N4(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_N3(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_N2(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_N1(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_0(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_1(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_2(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_3(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_4(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_5(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_height(const vector<bool> bs, const int b);

int blk_test_fn__random_excursion_depth(const vector<bool> bs, const int b);

int explicit_template_match_test(const vector<bool> bs, const vector<bool> templatee);

int blk_test_fn__template_match_4_1(const vector<bool> bs, const int b);

int blk_test_fn__template_match_4_2(const vector<bool> bs, const int b);

int blk_test_fn__template_match_4_3(const vector<bool> bs, const int b);

int blk_test_fn__template_match_4_4(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_1(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_2(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_3(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_4(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_5(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_6(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_7(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_8(const vector<bool> bs, const int b);

int blk_test_fn__template_match_9_9(const vector<bool> bs, const int b);

int blk_test_fn__disjoint_template_freq(const vector<bool> bs, const int b);

int blk_test_fn__disjoint_template_repeat(const vector<bool> bs, const int b);

int blk_test_fn__disjoint_template_coverage(const vector<bool> bs, const int b);

int blk_test_fn__disjoint_template_saturation(const vector<bool> bs, const int b);

int blk_test_fn__disjoint_template_int_max(const vector<bool> bs, const int b);

int blk_test_fn__disjoint_template_int_min(const vector<bool> bs, const int b);

int blk_test_fn__disjoint_template_int_dif(const vector<bool> bs, const int b);

int blk_test_fn__linear_complexity(const vector<bool> bs, const int blksz);

int blk_test_fn__linear_complexity_profile(const vector<bool> bs, const int b);

int blk_test_fn__blind_spot_complexity(const vector<bool> bs, const int blksz);

int blk_test_fn__blind_spot_complexity_profile(const vector<bool> bs, const int b);

#endif
