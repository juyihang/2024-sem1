
#include "C:\\Users\\H\\CLionProjects\\WZQ AI\\CHESS_GAME\\CHESS_GAME_SOURCE.h"
#include "Max-Min_Search.h"
#include "Zorbists.h"
#include <graphics.h>

inline bool AI_Finish_Put_Process(Chess_Board &p,int AIDepth){
    Board_State To_WIN=IDA_DeeperSearch(MainBoard,AIDepth,ComPlayerSide);
    p.board[To_WIN.steps[0].x][To_WIN.steps[0].y]=ComPlayerSide;
    p.Last_x=To_WIN.steps[0].x,p.Last_y=To_WIN.steps[0].y;
    AllSteps.push_back(To_WIN.steps[0]);
    return true;
}

bool Chess_Process_With_AI(Chess_Board &p,int Screen_Width,int Screen_Height,int IsFirstPut,int AIDepth,int QUICK_Limit,bool EnableQUICK,bool EnableHash){

    InitZorbists();

    QUICK_LIMIT=QUICK_Limit;


    if(IsFirstPut) HumPlayerSide=1,ComPlayerSide=0;
    else HumPlayerSide=0,ComPlayerSide=1;
    MainBoard.Current_Player=0;
    p.SC_WIDTH=Screen_Width,p.SC_HEIGHT=Screen_Height;

    initgraph(Screen_Width, Screen_Height);
    loadimage(NULL, "C:/Users/H/Desktop/IMG/bg.jpg",Screen_Width,Screen_Height);
    //cleardevice();
    setlinecolor(BLACK);
    Calc_Width=Screen_Width*0.8/14;
    Calc_Height=Screen_Height*0.8/14;
    for(double i=0;i<15;i+=1){
        IsThick^=1;
        setlinestyle(PS_SOLID,IsThick+2);
        line(Screen_Width*0.1+i*Calc_Width,Screen_Height*0.1,Screen_Width*0.1+i*Calc_Width,Screen_Height*0.9);
    }
    IsThick=0;
    for(double i=0;i<15;i+=1){
        IsThick^=1;
        setlinestyle(PS_SOLID,IsThick+2);
        line(Screen_Width*0.1,Screen_Height*0.1+i*Calc_Height,Screen_Width*0.9,Screen_Height*0.1+i*Calc_Height);
    }

    CHESS_INIT(p);
    while(!Check_Checkmate(p,p.Last_x,p.Last_y)){
        p.Current_Player^=1;
        if(p.Current_Player==HumPlayerSide) Put_Chess(p);
        else{

            if(EnableHash){
                PUT BOOK_ANSWER=Find_Same_Board(Zorbist_HASH_Value);
                if(BOOK_ANSWER.x!=-1){
                    p.board[BOOK_ANSWER.x][BOOK_ANSWER.y]=ComPlayerSide;
                    p.Last_x=BOOK_ANSWER.x,p.Last_y=BOOK_ANSWER.y;
                    AllSteps.push_back(BOOK_ANSWER);
                }
                else AI_Finish_Put_Process(p,AIDepth);
            }
            else{
                AI_Finish_Put_Process(p,AIDepth);
            }

        }
        Calc_PUT_Zorbist({p.Last_x,p.Last_y}, p.Current_Player);

        Draw_A_PixelChesspiece(p.Last_x,p.Last_y,Screen_Width/50,p.Current_Player);
        p.Put_Count++;
        if(p.Put_Count>=225&&!Check_Checkmate(p,p.Last_x,p.Last_y)) return false;
    }
    return true;
}
