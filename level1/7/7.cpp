#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;
const int MAXN=160;
char map[MAXN][MAXN];
bool flag=0;
int px,py,mx,my;
// @ exit  # border P player * entrance . path
inline bool jud(int x,int y){
    if(x<0||y<0||x>=mx||y>=my) return false;
    if(map[x][y]=='#') return false;
    if(map[x][y]=='@'){
        flag=1;
    }
    px=x,py=y;
    return true;
}
inline void printmap(){
    for(int i=0;i<mx;i++){
        for(int j=0;j<my;j++){
            if(i==px&&j==py) cout<<'P';
            else cout<<map[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
inline void maze(){
    printmap();
    char opt=getch();
    if(opt==0||opt==224){
        switch(getch()){
            case 72:jud(px-1,py);
            case 75:jud(px,py-1);
            case 80:jud(px+1,py);
            case 77:jud(px,py+1);
        }
    }
    else{
        if(opt=='w'||opt=='W')jud(px-1,py);
        else if(opt=='a'||opt=='A')jud(px,py-1);
        else if(opt=='s'||opt=='S')jud(px+1,py);
        else if(opt=='d'||opt=='D')jud(px,py+1);
    }

}
int main(){
    //input maze
    //check exit pos
    cin>>mx>>my;
    for(int i=0;i<mx;i++){
        for(int j=0;j<my;j++){
            cin>>map[i][j];
            if(map[i][j]=='*'){
                px=i,py=j;
            }
        }
    }
    //start
    while(!flag){
        maze();
        _sleep(50);
        system("cls");
        _sleep(20);
    }
    printmap();
    cout<<endl;
    cout<<"Stage Clear"<<endl;
    return 0;
}