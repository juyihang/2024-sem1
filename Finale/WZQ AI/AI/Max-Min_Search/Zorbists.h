
#pragma once

#include "Max-Min_Search.h"
#include <random>
#include <map>

typedef long long LL;
extern std::mt19937 myrand;
extern std::map<LL,LL> Zorbist_HASH;

extern LL Zorbist_HASH_Value;
extern LL Zorbist_Value[16][16][4];

inline LL GetZorbistInitNumber();
void InitZorbists();
void Calc_PUT_Zorbist(PUT p,int role);
PUT Find_Same_Board(LL Key);