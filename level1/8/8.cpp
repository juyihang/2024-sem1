#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>
using namespace std;
const int MAXN=160;
char map[MAXN][MAXN];
bool box[MAXN][MAXN];
int px,py,mx,my,score,step,perfectsteps,num,res,a;
// @ spawn  # border P player O box . path X dest
inline void pushbox(int x,int y,int dir){
    if(dir==1&&x-1>=0){
        if(map[x-1][y]!='#'&&map[x-1][y]!='O') box[x-1][y]=1,box[x][y]=0;
    }
    else if(dir==2&&y-1>=0){
        if(map[x][y-1]!='#'&&map[x][y-1]!='O') box[x][y-1]=1,box[x][y]=0;
    }
    else if(dir==3&&x+1<mx){
        if(map[x+1][y]!='#'&&map[x+1][y]!='O') box[x+1][y]=1,box[x][y]=0;
    }
    else if(dir==4&&y+1<my){
        if(map[x][y+1]!='#'&&map[x][y+1]!='O') box[x][y+1]=1,box[x][y]=0;
    }
}
inline bool jud(int x,int y,int dir){
    if(x<0||y<0||x>=mx||y>=my) return false;
    if(map[x][y]=='#') return false;
    if(box[x][y]){
        pushbox(x,y,dir);
    }
    px=x,py=y;
    return true;
}
inline void printmap(){
    score=0;
    for(int i=0;i<mx;i++){
        for(int j=0;j<my;j++){
            if(i==px&&j==py) cout<<'P';
            else if(map[i][j]=='X'){
                if(box[i][j]) cout<<"O",score++;
                else cout<<'X';
            }
            else if(box[i][j]) cout<<"O";
            else cout<<map[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
inline void maze(){
    printmap();
    char opt=getch();
    if((int)opt==0||(int)opt==224){
        switch((int)getch()){
            case 72:jud(px-1,py,1);
            case 75:jud(px,py-1,2);
            case 80:jud(px+1,py,3);
            case 77:jud(px,py+1,4);
        }
    }
    else{
        if(opt=='w'||opt=='W')jud(px-1,py,1);
        else if(opt=='a'||opt=='A')jud(px,py-1,2);
        else if(opt=='s'||opt=='S')jud(px+1,py,3);
        else if(opt=='d'||opt=='D')jud(px,py+1,4);
    }

}
int main(){
    //input maze
    cout<<"please select the level from 1 to 5 "<<endl;
    cin>>a;
    fstream infile;
    if(a==1) infile.open("level1.txt");
    else if(a==2) infile.open("level2.txt");
    else if(a==3) infile.open("level3.txt");
    else if(a==4) infile.open("level4.txt");
    else if(a==5) infile.open("level5.txt");
    else{
        cout<<"can't find the level"<<endl;
    }
    infile>>mx>>my>>perfectsteps;
    for(int i=0;i<mx;i++){
        for(int j=0;j<my;j++){
            infile>>map[i][j];
            if(map[i][j]=='@'){
                px=i,py=j;map[i][j]='.';
            }
            if(map[i][j]=='O') map[i][j]='.',num++,box[i][j]=1;
        }
    }
    infile.close();
    //start
    while(score<num){
        maze();
        _sleep(50);
        system("cls");
        _sleep(20);
    }
    printmap();
    cout<<endl;
    cout<<"Stage Clear"<<endl;
    cout<<score<<endl;
    fstream outfile("record.txt",ios::app);
    outfile<<"In level "<<a<<" : "<<score<<endl;
    outfile.close();
    return 0;
}