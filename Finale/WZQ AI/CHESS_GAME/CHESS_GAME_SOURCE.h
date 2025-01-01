
#ifndef CHESS
#define CHESS

struct Chess_Board{
    int board[16][16];
    int Check_Direction[9][2];
    int Current_Player=1;
    int Put_Count=0;
    int Last_x,Last_y;
    int Last_2x,Last_2y;
    int Last_MKx,Last_MKy;
    int SC_WIDTH,SC_HEIGHT;
};

extern Chess_Board MainBoard;
extern int HumPlayerSide,ComPlayerSide;
extern int IsThick;
extern double Calc_Width,Calc_Height;
extern int BOARD_LENGTH;
extern int BEALINE;
extern int EMPTY;

void CHESS_INIT(Chess_Board &p);
inline bool Put_Success(Chess_Board &p,int x,int y);
void Get_Mouse_Location(Chess_Board &p,int &x,int &y);
bool Put_Chess(Chess_Board &p);
bool Cancel_Chess(Chess_Board &p);
bool Check_Checkmate(Chess_Board &p,int x,int y);
void Draw_A_PixelChesspiece(int x,int y,int radius,int color);
void ShowLastPutLocation(Chess_Board &p,int x,int y);
void Draw_PixelChess_Map(int Screen_Width,int Screen_Height);
bool Chess_Process_Without_AI(Chess_Board &p,int Screen_Width,int Screen_Height,int IsFirstPut);

#endif