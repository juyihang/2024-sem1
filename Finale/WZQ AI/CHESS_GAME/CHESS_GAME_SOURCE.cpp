
//#include "CHESS_GAME_SOURCE.h"
#include <cstring>
#include <graphics.h>
#include <conio.h>

using namespace std;

struct Chess_Board{
    int board[16][16];
    int Check_Direction[9][2];
    int Current_Player=1;
    int Put_Count=0;
    int Last_x,Last_y;
    int Last_2x,Last_2y;
    int Last_MKx,Last_MKy;
    int SC_WIDTH,SC_HEIGHT;
} MainBoard;

int HumPlayerSide,ComPlayerSide;
int IsThick=0;
double Calc_Width,Calc_Height;
int BOARD_LENGTH=15;
int BEALINE=5;
int EMPTY=-1;

void CHESS_INIT(Chess_Board &p){
    memset(p.board,-1,sizeof(p.board));
    //右 左 下 上 右下 左上 右上 左下
    p.Check_Direction[1][0]=1,p.Check_Direction[1][1]=0;
    p.Check_Direction[2][0]=-1,p.Check_Direction[2][1]=0;
    p.Check_Direction[3][0]=0,p.Check_Direction[3][1]=1;
    p.Check_Direction[4][0]=0,p.Check_Direction[4][1]=-1;
    p.Check_Direction[5][0]=1,p.Check_Direction[5][1]=1;
    p.Check_Direction[6][0]=-1,p.Check_Direction[6][1]=-1;
    p.Check_Direction[7][0]=1,p.Check_Direction[7][1]=-1;
    p.Check_Direction[8][0]=-1,p.Check_Direction[8][1]=1;
}

inline bool Put_Success(Chess_Board &p,int x,int y){
    if(p.board[x][y]==-1) return true;
    return false;
}

void Draw_A_PixelChesspiece(int x,int y,int radius,int color);

void Get_Mouse_Location(Chess_Board &p,int &x,int &y){
    ExMessage msg;
    int FLG_ISCLICKED=0;

    while(FLG_ISCLICKED!=2){
        while(peekmessage(&msg)){
            FLG_ISCLICKED=0;
            switch(msg.message){
                case WM_LBUTTONDOWN:
                    for(int i=1;i<=BOARD_LENGTH;i++){
                        if(msg.x>=0.1*p.SC_WIDTH+(i-1)*Calc_Width-Calc_Width/2&&msg.x<=0.1*p.SC_WIDTH+(i-1)*Calc_Width+Calc_Width/2){
                            x=i;
                            FLG_ISCLICKED++;
                            break;
                        }
                    }
                    for(int i=1;i<=BOARD_LENGTH;i++){
                        if(msg.y>=0.1*p.SC_HEIGHT+(i-1)*Calc_Height-Calc_Height/2&&msg.y<=0.1*p.SC_HEIGHT+(i-1)*Calc_Height+Calc_Height/2){
                            y=i;
                            FLG_ISCLICKED++;
                            break;
                        }
                    }
                    break;
                case WM_MOUSEMOVE:
                    for(int i=1;i<=BOARD_LENGTH;i++){
                        if(msg.x>=0.1*p.SC_WIDTH+(i-1)*Calc_Width-Calc_Width/2&&msg.x<=0.1*p.SC_WIDTH+(i-1)*Calc_Width+Calc_Width/2){
                            x=i;
                            FLG_ISCLICKED++;
                            break;
                        }
                    }
                    for(int i=1;i<=BOARD_LENGTH;i++){
                        if(msg.y>=0.1*p.SC_HEIGHT+(i-1)*Calc_Height-Calc_Height/2&&msg.y<=0.1*p.SC_HEIGHT+(i-1)*Calc_Height+Calc_Height/2){
                            y=i;
                            FLG_ISCLICKED++;
                            break;
                        }
                    }
                    if(FLG_ISCLICKED==2&&p.board[x][y]==EMPTY){
                        if(p.Last_MKx!=x||p.Last_MKy!=y) {
                            if(p.Last_MKx!=0&&p.board[p.Last_MKx][p.Last_MKy]==EMPTY) clearcircle((int)((p.Last_MKx-1)*Calc_Width+p.SC_WIDTH*0.1),(int)((p.Last_MKy-1)*Calc_Height+p.SC_HEIGHT*0.1),p.SC_WIDTH/240);
                            setfillcolor(LIGHTRED);
                            solidcircle((int)((x-1)*Calc_Width+p.SC_WIDTH*0.1),(int)((y-1)*Calc_Height+p.SC_HEIGHT*0.1),p.SC_WIDTH/240);
                            p.Last_MKx=x;
                            p.Last_MKy=y;
                        }
                    }
                    else if(p.board[x][y]!=EMPTY){
                        if(p.Last_MKx!=0&&p.board[p.Last_MKx][p.Last_MKy]==EMPTY) clearcircle((int)((p.Last_MKx-1)*Calc_Width+p.SC_WIDTH*0.1),(int)((p.Last_MKy-1)*Calc_Height+p.SC_HEIGHT*0.1),p.SC_WIDTH/240);
                        p.Last_MKx=0;
                        p.Last_MKy=0;
                    }
                    FLG_ISCLICKED=0;
                    break;
            }
        }
    }

}

void Draw_A_PixelChesspiece(int x,int y,int radius,int color){
    if(color==1) setfillcolor(BLACK);
    else setfillcolor(WHITE);
    solidcircle((int)((x-1)*Calc_Width+MainBoard.SC_WIDTH*0.1),(int)((y-1)*Calc_Height+MainBoard.SC_HEIGHT*0.1),radius);
}

void Draw_PixelChess_Map(int Screen_Width,int Screen_Height){
    //I don't know why can't use inner function to build map;
}

void ShowLastPutLocation(Chess_Board &p,int x,int y){
    // clear last DRAW

    // Draw


}

bool Put_Chess(Chess_Board &p){
    int mx,my;

    do{
        mx=-1;my=-1;
        while(mx==-1||my==-1) Get_Mouse_Location(p,mx,my);
    }while(!Put_Success(p,mx,my));

    p.board[mx][my]=p.Current_Player;
    if(p.Last_x!=0) p.Last_2x=p.Last_x,p.Last_2y=p.Last_y;
    p.Last_x=mx,p.Last_y=my;
    return true;
}

bool Cancel_Chess(Chess_Board &p){

    // 弹窗询问


    p.board[p.Last_2x][p.Last_2y]=EMPTY;
    p.board[p.Last_x][p.Last_y]=EMPTY;

    //撤销绘制棋子


    return true;
}

bool Check_Checkmate(Chess_Board &p,int x,int y){
    int Same_Count;
    for(int i=1;i<=8;i+=2){
        Same_Count=0;
        if(x+4*p.Check_Direction[i][0]>=1&&x+4*p.Check_Direction[i][0]<=15&&y+4*p.Check_Direction[i][1]>=1&&y+4*p.Check_Direction[i][1]<=15){
            for(int ix=x,iy=y;;ix+=p.Check_Direction[i][0],iy+=p.Check_Direction[i][1]){
                if(p.board[ix][iy]==p.Current_Player) Same_Count++;
                if(Same_Count==5) return true;
                if(p.board[ix][iy]!=p.Current_Player&&Same_Count<5) break;
            }
        }
        if(Same_Count==5) return true;
        Same_Count--;
        if(x+4*p.Check_Direction[i+1][0]>=1&&x+4*p.Check_Direction[i+1][0]<=15&&y+4*p.Check_Direction[i+1][1]>=1&&y+4*p.Check_Direction[i+1][1]<=15){
            for(int ix=x,iy=y;;ix+=p.Check_Direction[i+1][0],iy+=p.Check_Direction[i+1][1]){
                if(p.board[ix][iy]==p.Current_Player) Same_Count++;
                if(Same_Count==5) return true;
                if(p.board[ix][iy]!=p.Current_Player&&Same_Count<5) break;
            }
        }
    }
    for(int i=2;i<=8;i+=2){
        Same_Count=0;
        if(x+4*p.Check_Direction[i][0]>=1&&x+4*p.Check_Direction[i][0]<=15&&y+4*p.Check_Direction[i][1]>=1&&y+4*p.Check_Direction[i][1]<=15){
            for(int ix=x,iy=y;;ix+=p.Check_Direction[i][0],iy+=p.Check_Direction[i][1]){
                if(p.board[ix][iy]==p.Current_Player) Same_Count++;
                if(Same_Count==5) return true;
                if(p.board[ix][iy]!=p.Current_Player&&Same_Count<5) break;
            }
        }
        if(Same_Count==5) return true;
        Same_Count--;
        if(x+4*p.Check_Direction[i-1][0]>=1&&x+4*p.Check_Direction[i-1][0]<=15&&y+4*p.Check_Direction[i-1][1]>=1&&y+4*p.Check_Direction[i-1][1]<=15){
            for(int ix=x,iy=y;;ix+=p.Check_Direction[i-1][0],iy+=p.Check_Direction[i-1][1]){
                if(p.board[ix][iy]==p.Current_Player) Same_Count++;
                if(Same_Count==5) return true;
                if(p.board[ix][iy]!=p.Current_Player&&Same_Count<5) break;
            }
        }
    }
    return false;
}

//Chess_Process(MainBoard , 900, 900 ,1); entrance
//白0 黑1
bool Chess_Process_Without_AI(Chess_Board &p,int Screen_Width,int Screen_Height,int IsFirstPut){
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
    setbkmode(TRANSPARENT);
    CHESS_INIT(p);
    while(!Check_Checkmate(p,p.Last_x,p.Last_y)){
        p.Current_Player^=1;
        Put_Chess(p);
        Draw_A_PixelChesspiece(p.Last_x,p.Last_y,Screen_Width/50,p.Current_Player);
        p.Put_Count++;
        if(p.Put_Count>=225&&!Check_Checkmate(p,p.Last_x,p.Last_y)) return false;
    }
    return true;
}