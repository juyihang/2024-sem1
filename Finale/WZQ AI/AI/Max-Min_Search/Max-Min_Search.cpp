
#include "C:\\Users\\H\\CLionProjects\\WZQ AI\\CHESS_GAME\\CHESS_GAME_SOURCE.h"
#include <algorithm>
#include <graphics.h>
#include <vector>
#include <memory>

const int MIN_SCORE=-0x7fffffff;

int SC_FIVE,SC_FOUR,SC_BFOUR,SC_THREE,SC_TWO,SC_ONE;
int MAX,MIN,QUICK_LIMIT;
bool HasChecked[16][16];
const int COUNT_LIMIT=185;
std::vector<std::vector<int>> HUMSCORE(BOARD_LENGTH+1,std::vector<int>(BOARD_LENGTH+1));
std::vector<std::vector<int>> COMSCORE(BOARD_LENGTH+1,std::vector<int>(BOARD_LENGTH+1));


struct Put_Location{
    int x,y,HumScore,ComScore,score;

    bool operator<(const Put_Location& OTHER) const{
        return score<OTHER.score;
    }
};
typedef Put_Location PUT;
std::vector<PUT> AllSteps;

struct Board_State{
    int score;
    int step;
    std::vector<PUT> steps;
};

int Put_Board(Chess_Board &Board,PUT p,int role){
    if(Board.board[p.x][p.y]==EMPTY){
        Board.board[p.x][p.y]=role;
        return 1;
    }
    else return -1;
}

int Remove_Board(Chess_Board &Board,PUT p){
    if(Board.board[p.x][p.y]!=EMPTY){
        Board.board[p.x][p.y]=EMPTY;
        return 1;
    }
    return -1;
}

inline bool CheckValid(Chess_Board &Board,int x,int y,int i,int multi){
    if(x+multi*Board.Check_Direction[i][0]<0||x+multi*Board.Check_Direction[i][0]>BOARD_LENGTH) return false;
    if(y+multi*Board.Check_Direction[i][1]<0||y+multi*Board.Check_Direction[i][1]>BOARD_LENGTH) return false;
    return true;
}

bool HasNeighbor(Chess_Board &Board,int x,int y,int mul){
    for(int i=1;i<=8;i++){
        for(int j=1;j<=mul;j++){
            if(CheckValid(MainBoard,x,y,i,j)){
                if(Board.board[x+j*Board.Check_Direction[i][0]][y+j*Board.Check_Direction[i][1]]!=EMPTY) return true;
            }
        }
    }
    return false;
}

int Calc_Position_Value(Chess_Board &Board,int x,int y,int role){
    int Position_Score=0;
    int Same_Count;
    bool IsBlocked;
    for(int i=1;i<=8;i+=2){
        Same_Count=0;
        IsBlocked=false;
        for(int ix=x,iy=y,tot=1;tot<=BEALINE;ix+=Board.Check_Direction[i][0],iy+=Board.Check_Direction[i][1],tot++){
            if(ix<=0||ix>BOARD_LENGTH) break;
            if(iy<=0||iy>BOARD_LENGTH) break;
            if(Board.board[ix][iy]==role) Same_Count++;
            else if(Board.board[ix][iy]==(role^1)){
                IsBlocked=true;break;
            }
            else break;
        }
        Same_Count--;
        for(int ix=x,iy=y,tot=1;tot<=BEALINE;ix+=Board.Check_Direction[i+1][0],iy+=Board.Check_Direction[i+1][1],tot++){
            if(ix<=0||ix>BOARD_LENGTH) break;
            if(iy<=0||iy>BOARD_LENGTH) break;
            if(Board.board[ix][iy]==role) Same_Count++;
            else if(Board.board[ix][iy]==(role^1)){
                IsBlocked=true;break;
            }
            else break;
        }
        if(Same_Count==5) Position_Score+=SC_FIVE;
        else if(Same_Count==4&&IsBlocked){
            Position_Score+=SC_BFOUR;
        }
        else if(Same_Count==4) Position_Score+=SC_FOUR;
        else if(Same_Count==3) Position_Score+=SC_THREE;
        else if(Same_Count==2) Position_Score+=SC_TWO;
        else if(Same_Count==1) Position_Score+=SC_ONE;
    }
    return Position_Score;
}

void InitEvaluationScore(Chess_Board &p){
//    SC_FIVE=13000;
//    SC_BFOUR=6000;
//    SC_FOUR=8000;
//    SC_THREE=4500;
//    SC_TWO=1510;
//    SC_ONE=0;
    SC_FIVE=10000;
    SC_BFOUR=100;
    SC_FOUR=1000;
    SC_THREE=100;
    SC_TWO=10;
    SC_ONE=1;

    MAX=1000000;
    MIN=-MAX;
}

int Evaluate_Board(Chess_Board &Board,int role){

    //hash

    int Total_Score=0;
    for(int i=1;i<=BOARD_LENGTH;i++){
        for(int j=1;j<=BOARD_LENGTH;j++){
            if(HasNeighbor(Board,i,j,1)){
                if(role==ComPlayerSide){
                    COMSCORE[i][j]=Calc_Position_Value(Board,i,j,role);;
                    Total_Score+=COMSCORE[i][j];
                }
                else{
                    HUMSCORE[i][j]=Calc_Position_Value(Board,i,j,role);;
                    Total_Score+=HUMSCORE[i][j];
                }
            }
        }
    }
    return Total_Score;
}

std::vector<PUT> concat(const std::vector<PUT>& a, const std::vector<PUT>& b) {
    std::vector<PUT> result(a);
    result.insert(result.end(), b.begin(), b.end());
    return result;
}

std::vector<PUT> Generate_Board(Chess_Board &Board,int role,bool OnlyThrees,bool StarSpread){
    //if no chess in board, return 8,8
    if(Board.Put_Count==0) return {{8,8}};

    std::vector<PUT> BothFive;
    std::vector<PUT> ComFours,ComDeadFours,ComTwoThrees,ComThrees,ComTwos;
    std::vector<PUT> HumFours,HumDeadFours,HumTwoThrees,HumThrees,HumTwos;
    std::vector<PUT> neighbors;
    int Opponent_Role=role^1;

    for(int i=1;i<=BOARD_LENGTH;i++){
        for(int j=1;j<=BOARD_LENGTH;j++){
            if(Board.board[i][j]==EMPTY){

                int Search_Range;
                if(AllSteps.size()<6) Search_Range=3;
                else Search_Range=6;

                if(HasNeighbor(Board,i,j,Search_Range)){
                    PUT p={i,j,HUMSCORE[i][j],COMSCORE[i][j]};
                    Put_Board(Board,p,HumPlayerSide);
                    int Hum_Score=Calc_Position_Value(Board,i,j,HumPlayerSide);
                    Remove_Board(Board,p);
                    Put_Board(Board,p,ComPlayerSide);
                    int Com_Score=Calc_Position_Value(Board,i,j,ComPlayerSide);
                    Remove_Board(Board,p);
                    int Max_Score;
                    Max_Score=((Hum_Score) > (Com_Score)) ? (Hum_Score) : (Com_Score);
                    p.score=Max_Score;
                    if(Com_Score>SC_FIVE){
                        BothFive.push_back(p);
                    }
                    else if(Hum_Score>SC_FIVE){
                        BothFive.push_back(p);
                    }
                    else if(Com_Score>SC_FOUR){
                        ComFours.push_back(p);
                    }
                    else if(Hum_Score>SC_FOUR){
                        HumFours.push_back(p);
                    }
                    else if(Com_Score>SC_BFOUR){
                        ComDeadFours.push_back(p);
                    }
                    else if(Hum_Score>SC_BFOUR){
                        HumDeadFours.push_back(p);
                    }
                    else if(Com_Score>2*SC_THREE){
                        ComTwoThrees.push_back(p);
                    }
                    else if(Hum_Score>2*SC_THREE){
                        HumTwoThrees.push_back(p);
                    }
                    else if(Com_Score>SC_THREE){
                        ComThrees.push_back(p);
                    }
                    else if(Hum_Score>SC_THREE){
                        HumThrees.push_back(p);
                    }
                    else if(Com_Score>SC_TWO){
                        ComTwos.push_back(p);
                    }
                    else if(Hum_Score>SC_TWO){
                        HumTwos.push_back(p);
                    }
                    else{
                        neighbors.push_back(p);
                    }
                }
            }
        }
    }
    //成五
    if(!BothFive.empty()) return BothFive;

    //自己有活四直接用
    if(role==ComPlayerSide&&!ComFours.empty()) return ComFours;
    if(role==HumPlayerSide&&!HumFours.empty()) return HumFours;

    //对面有四但自己没四 认为对手只选活四
    if(role==ComPlayerSide&&ComDeadFours.empty()&&!HumFours.empty()) return HumFours;
    if(role==HumPlayerSide&&HumDeadFours.empty()&&!ComFours.empty()) return ComFours;

    //对手有活四  自己有四无活  先全选上
    std::vector<PUT> Fours;
    std::vector<PUT> DeadFours;
    if(!HumFours.empty()||!ComFours.empty()||!HumDeadFours.empty()||!ComDeadFours.empty()){
        if(role==ComPlayerSide){
            ComFours=concat(ComFours,HumFours);
            ComDeadFours=concat(ComDeadFours,HumDeadFours);
            Fours=concat(Fours,ComFours);
            DeadFours=concat(DeadFours,ComDeadFours);
        }
        else{
            HumFours=concat(HumFours,ComFours);
            HumDeadFours=concat(HumDeadFours,ComDeadFours);
            Fours=concat(Fours,HumFours);
            DeadFours=concat(DeadFours,HumDeadFours);
        }
    }
    if(!Fours.empty()) return concat(Fours,DeadFours);

    std::vector<PUT> Choice_Group;
    if(role==ComPlayerSide){
        Choice_Group=concat(Choice_Group,ComTwoThrees);
        Choice_Group=concat(Choice_Group,HumTwoThrees);
        Choice_Group=concat(Choice_Group,ComDeadFours);
        Choice_Group=concat(Choice_Group,HumDeadFours);
        Choice_Group=concat(Choice_Group,ComThrees);
        Choice_Group=concat(Choice_Group,HumThrees);
    }
    else{
        Choice_Group=concat(Choice_Group,HumTwoThrees);
        Choice_Group=concat(Choice_Group,ComTwoThrees);
        Choice_Group=concat(Choice_Group,HumDeadFours);
        Choice_Group=concat(Choice_Group,ComDeadFours);
        Choice_Group=concat(Choice_Group,HumThrees);
        Choice_Group=concat(Choice_Group,ComThrees);
    }

    //如果有两个三
    if(!ComTwoThrees.empty()||!HumTwoThrees.empty()){
        return Choice_Group;
    }

    if(OnlyThrees) return Choice_Group;

    //二  然后 一
    std::vector<PUT> Twos=(role==ComPlayerSide) ? concat(ComTwos, HumTwos):concat(HumTwos, ComTwos);
    std::sort(Twos.begin(), Twos.end(), [&](const PUT& a, const PUT& b) ->bool {
        return a.score>b.score; // Sort based on score
    });
    Choice_Group=concat(Choice_Group,(Twos.empty())? neighbors: Twos);
    if(Choice_Group.size()>COUNT_LIMIT){
        Choice_Group.resize(COUNT_LIMIT);
    }
    return Choice_Group;
}

Board_State State_Init(Board_State &boardstate, int score, int step, std::vector<PUT> &steps){
    boardstate.score=score;
    boardstate.step=step;
    boardstate.steps=steps;
    return boardstate;
}

//        如果电脑先手  优先指定放棋子到特殊位置
//                             8                            Current   // NULL     NULL          1
// 人类玩家放置到棋盘边缘会导致程序对棋盘局势判断失智    待优化
Board_State Max_Min_Search(int depth,int alpha,int beta,int role,int step,std::vector<PUT> &steps,bool spread){
    int Role_Score= Evaluate_Board(MainBoard,role);
    Board_State Leaf,Best_State;
    Leaf=State_Init(Leaf,Role_Score,step,steps);
    if(depth==0) return Leaf;
    Best_State=State_Init(Best_State,MIN_SCORE,step,steps);
    std::vector<PUT> points;
    if(step>QUICK_LIMIT) points=Generate_Board(MainBoard,role,true,true);
    else points=Generate_Board(MainBoard,role,false,true);
    if(points.empty()) return Leaf;

    for(int i=0;i<points.size();i++){
        PUT p=points[i];

        Put_Board(MainBoard,p,role);

        int New_Depth=depth-1;
        int New_Spread=spread;
        std::vector<PUT> New_Steps=steps;
        New_Steps.push_back(p);

        Board_State New_State= Max_Min_Search(New_Depth,-beta,-alpha,role^1,step+1,New_Steps,New_Spread);
        New_State.score=New_State.score*-1;
        Remove_Board(MainBoard,p);
        if(New_State.score>Best_State.score){
            Best_State.score=New_State.score;
            Best_State.step=New_State.step;
            Best_State.steps=New_State.steps;
        }
        if(Best_State.score>alpha) alpha=Best_State.score;
        if(New_State.score>=beta) return New_State;
    }

    return Best_State;
}

Board_State IDA_DeeperSearch(Chess_Board &p,int ExpectedDepth,int role){
    std::vector<Board_State> Possible_States;
    InitEvaluationScore(MainBoard);

    for(int i=2;i<=ExpectedDepth;i+=2){
        std::vector<PUT> EMPTY;
        Possible_States.push_back(Max_Min_Search(i,MAX,MIN,role,1, EMPTY,0));
        if(Possible_States[i/2-1].score>SC_FIVE) break;
    }

    std::sort(Possible_States.begin(),Possible_States.end(),[&](const Board_State& a,const Board_State& b)->bool{
        return a.score>b.score;
    });

    return Possible_States[0];
}

//ComputerSide_Put_Chess(MainBoard,IDA_DeeperSearch(MainBoard,4,ComputerPlayerSide));
//AllSteps.push_back(HumPlayerStep);     To be added
