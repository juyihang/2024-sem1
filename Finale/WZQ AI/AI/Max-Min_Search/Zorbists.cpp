//zorbist

#include "Max-Min_Search.h"
#include <fstream>
#include <random>
#include <ctime>
#include <map>

typedef long long LL;
const int TABLE_SIZE=15;
const int POSSIBLE_STATE=3;
// 1 BLACK  2 WHITE  3 EMPTY

std::mt19937 myrand(time(nullptr));

std::map<LL,PUT> Zorbist_HASH;
//    Key     Score

LL Zorbist_HASH_Value;
LL Zorbist_Value[TABLE_SIZE+1][TABLE_SIZE+1][POSSIBLE_STATE+1];


inline LL GetZorbistInitNumber(){
    return myrand();
}

void InitZorbists(){
    std::fstream Zorbist("ZorbistInitialKey.txt");
    if(Zorbist){
        for(int i=1;i<=TABLE_SIZE;i++){
            for(int j=1;j<=TABLE_SIZE;j++){
                for(int k=1;k<=POSSIBLE_STATE;k++){
                    Zorbist>>Zorbist_Value[i][j][k];
                }
                Zorbist_HASH_Value^=Zorbist_Value[i][j][3];
            }
        }
    }
    else for(int i=1;i<=TABLE_SIZE;i++){
        for(int j=1;j<=TABLE_SIZE;j++){
            for(int k=1;k<=POSSIBLE_STATE;k++){
                Zorbist_Value[i][j][k] = GetZorbistInitNumber();
                Zorbist<<Zorbist_Value[i][j][k]<<" ";
            }
            Zorbist<<std::endl;
            Zorbist_HASH_Value^=Zorbist_Value[i][j][3];
        }
    }
}


// 1 BLACK  2 WHITE
void Calc_PUT_Zorbist(PUT p,int role){
    Zorbist_HASH_Value=Zorbist_HASH_Value^Zorbist_Value[p.x][p.y][3]^Zorbist_Value[p.x][p.y][role];
    Zorbist_HASH.insert({Zorbist_HASH_Value,p});
}

PUT Find_Same_Board(LL Key){
    if(Zorbist_HASH.find(Key)!=Zorbist_HASH.end()) return Zorbist_HASH[Key];
    else return {-1,-1};
}



int CONFIG_CALC_LIMIT;