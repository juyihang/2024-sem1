
#include "CHESS_GAME/CHESS_GAME_SOURCE.h"
#include "AI/Max-Min_Search/Max-Min_Search.h"
#include <algorithm>

int MAX_SCORE;
int MIN_SCORE;
PUT LastMaxPoint,LastMinPoint;

std::vector<PUT> FIND_MAX(Chess_Board &Board,int role,int score){

    std::vector<PUT> FIVES;
    std::vector<PUT> Choices;

    for(int i=1;i<=BOARD_LENGTH;i++){
        for(int j=1;j<=BOARD_LENGTH;j++){
            if(Board.board[i][j]==EMPTY){
                PUT p={i,j};
                int SC;
                if(role==ComPlayerSide) SC=COMSCORE[i][j];
                else if(role==HumPlayerSide) SC=HUMSCORE[i][j];
                p.score=SC;
                if(SC>=SC_FIVE) FIVES.push_back(p);
                if(SC>score) Choices.push_back(p);
            }
        }
    }

    if(FIVES.size()) return FIVES;

    sort(Choices.begin(),Choices.end(),[&](const PUT &a,const PUT &b)->bool{
        return a.score>b.score;
    });

    return Choices;
}

std::vector<PUT> FIND_MIN(Chess_Board &Board,int role,int score){
    std::vector<PUT> FIVES;
    std::vector<PUT> Choices;
    std::vector<PUT> FOURS;
    std::vector<PUT> DeadFOURS;

    for(int i=1;i<=BOARD_LENGTH;i++){
        for(int j=1;j<=BOARD_LENGTH;j++){
            if(Board.board[i][j]==EMPTY){
                PUT p={i,j};
                int SC1,SC2;
                if(role==ComPlayerSide){
                    SC1=COMSCORE[i][j];
                    SC2=HUMSCORE[i][j];
                }
                else if(role==HumPlayerSide){
                    SC2=COMSCORE[i][j];
                    SC1=HUMSCORE[i][j];
                }
                if(SC1>=SC_FIVE){
                    p.score=-SC1;
                    FIVES.push_back(p);
                    return FIVES;
                }
                if(SC2>=SC_FIVE){
                    p.score=SC2;
                    FIVES.push_back(p);
                    continue;
                }
                if(SC1>=SC_FOUR){
                    p.score=-SC1;
                    FOURS.push_back(p);
                }
                if(SC2>=SC_FOUR){
                    p.score=SC2;
                    FOURS.push_back(p);
                }
                if(SC1>=SC_BFOUR){
                    p.score=-SC1;
                    DeadFOURS.push_back(p);
                }
                if(SC2>=SC_BFOUR){
                    p.score=SC2;
                    DeadFOURS.push_back(p);
                }
                if(SC1>=score){
                    p.score=-SC1;
                    Choices.push_back(p);
                }
                if(SC2>=score){
                    p.score=SC2;
                    Choices.push_back(p);
                }
            }
        }
    }

    if(FIVES.size()) return FIVES;
    if(FOURS.size()) return concat(FOURS,DeadFOURS);
    Choices=concat(DeadFOURS,Choices);

    //sort

    return Choices;
}

std::vector<PUT> MAX_SEARCH(Chess_Board &Board,int role,int depth,int Total_Depth);
std::vector<PUT> MIN_SEARCH(Chess_Board &Board,int role,int depth,int Total_Depth);

std::vector<PUT> MAX_SEARCH(Chess_Board &Board,int role,int depth,int Total_Depth){
    std::vector<PUT> EmptyChoice;
    if(depth<=1) return EmptyChoice;
    std::vector<PUT> Choices= FIND_MAX(Board,role,MAX_SCORE);
    if(Choices.size()&&Choices[0].score>=SC_FOUR) return Choices;
    if(!Choices.size()) return EmptyChoice;
    for(int i=0;i<Choices.size();i++){
        PUT p=Choices[i];
        Put_Board(Board,p,role);
        if(p.score>-SC_FIVE) LastMaxPoint=p;
        std::vector<PUT> q;
        q= MIN_SEARCH(Board,role^1,depth-1,Total_Depth);
        Remove_Board(Board,p);
        if(q.size()){
            q.insert(q.begin(),p);
            return q;
        }
        else{
            EmptyChoice.push_back(p);
            return EmptyChoice;
        }
    }
    return EmptyChoice;
}

std::vector<PUT> MIN_SEARCH(Chess_Board &Board,int role,int depth,int Total_Depth){
    std::vector<PUT> EmptyChoice;



    if(depth<=1) return EmptyChoice;
    std::vector<PUT> Choices= FIND_MIN(Board,role,MAX_SCORE);
    if(Choices.size()&&-1*Choices[0].score>=SC_FOUR) return EmptyChoice;
    if(!Choices.size()) return EmptyChoice;
    for(int i=0;i<Choices.size();i++){
        PUT p=Choices[i];
        Put_Board(Board,p,role);
        if(p.score>-SC_FIVE) LastMinPoint=p;
        std::vector<PUT> q;
        q= MAX_SEARCH(Board,role^1,depth-1,Total_Depth);
        Remove_Board(Board,p);
        if(q.size()){
            q.insert(q.begin(),p);
            EmptyChoice= concat(EmptyChoice,q);
            continue;
        }
        else{
            return EmptyChoice;
        }
    }
    return EmptyChoice;
}

PUT Quick_IDA_DeeperSearch(int role,int depth,int Total_Depth){
    std::vector<PUT> Choices;
    int ExpectedDepth=8;
    for(int i=2;i<=ExpectedDepth;i+=2){
        std::vector<PUT> p= MAX_SEARCH(MainBoard,ComPlayerSide,i,Total_Depth);
        if(!p.size()) continue;
        if(p[0].score>MAX_SCORE) Choices.push_back(p[0]);
    }

    //sort

    if(Choices.size()) return Choices[0];
    else return {-1,-1};
}

PUT Get_VCX(int role,int depth,bool IsOnlyFour){
    PUT Choice={-1,-1};
    if(depth<=0) return Choice;
    if(IsOnlyFour){
        MAX_SCORE=SC_BFOUR;
        MIN_SCORE=SC_FIVE;
        Choice= Quick_IDA_DeeperSearch(role,depth,depth);
        if(Choice.x!=-1){
            Choice.score=SC_FOUR;
            return Choice;
        }
        return Choice;
    }
    else{
        MAX_SCORE=SC_BFOUR;
        MIN_SCORE=SC_FIVE;
        Choice= Quick_IDA_DeeperSearch(role,depth,depth);
        if(Choice.x!=-1){
            Choice.score=SC_THREE*2;
        }
        return Choice;
    }
    return {-1,-1,0,0,0};
}

inline PUT Get_VCF(int role,int depth){
    return Get_VCX(role,depth,true);
}

inline PUT Get_VCT(int role,int depth){
    return Get_VCX(role,depth,false);
}
