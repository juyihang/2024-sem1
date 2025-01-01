#pragma once

#include <vector>
#include "C:\\Users\\H\\CLionProjects\\WZQ AI\\CHESS_GAME\\CHESS_GAME_SOURCE.h"

extern int SC_FIVE,SC_FOUR,SC_BFOUR,SC_THREE,SC_TWO;
extern int MAX,MIN,QUICK_LIMIT;
extern bool HasChecked[16][16];
extern std::vector<std::vector<int>> HUMSCORE;
extern std::vector<std::vector<int>> COMSCORE;

struct Put_Location{
    int x,y,HumScore,ComScore,score;

    bool operator<(const Put_Location& OTHER) const{
        return score<OTHER.score;
    }
};
typedef Put_Location PUT;
extern std::vector<PUT> AllSteps;

struct Board_State{
    int score;
    int step;
    std::vector<PUT> steps;
};


inline bool CheckValid(Chess_Board &Board,int x,int y,int i,int multi);
bool HasNeighbor(Chess_Board &Board,int x,int y,int mul);
int Calc_Position_Value(Chess_Board &Board,int x,int y,int role);
void InitEvaluationScore(Chess_Board &p);
int Evaluate_Board(Chess_Board &Board,int role);
std::vector<PUT> concat(const std::vector<PUT>& a, const std::vector<PUT>& b);
std::vector<PUT> Generate_Board(Chess_Board &Board,int role,bool OnlyThrees,bool StarSpread);
int Put_Board(Chess_Board &Board,PUT p,int role);
int Remove_Board(Chess_Board &Board,PUT p);
Board_State State_Init(Board_State &boardstate, int score, int step, std::vector<PUT> &steps);
Board_State Max_Min_Search(int depth,int alpha,int beta,int role,int step,std::vector<PUT> steps,bool spread);
Board_State IDA_DeeperSearch(Chess_Board &p,int ExpectedDepth,int role);
