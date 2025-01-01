
#include <graphics.h>

void Draw_A_PixelChesspiece(int x,int y,int radius,int color){
    if(color==1) setfillcolor(BLACK);
    else setfillcolor(WHITE);
    solidcircle(x,y,radius);
}
void Draw_PixelChess_Map(int Screen_Width,int Screen_Height){
    initgraph(Screen_Width,Screen_Height,0);
    setbkcolor(YELLOW);
    cleardevice();
    double Calc_Width=Screen_Width*0.8;
    double Calc_Height=Screen_Height*0.8;
    for(double i=0;i<15;i+=1){
        line(Screen_Width*0.1+i/14*Calc_Width,Screen_Height*0.1,Screen_Width*0.9+i/14*Calc_Width,Screen_Height*0.1);
    }
    for(double i=0;i<15;i+=1){
        line(Screen_Width*0.1,Screen_Height*0.1+i/14*Calc_Height,Screen_Width*0.9,Screen_Height*0.1+i/14*Calc_Height);
    }
}