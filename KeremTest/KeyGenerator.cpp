#include "KeyGenerator.h"


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

