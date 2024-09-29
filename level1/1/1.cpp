#include <bits/stdc++.h>
using namespace std;
const int screenwidth=20;
const int DURINTE=1000;
inline void clearsc(){
    system("cls");
}
string a;
int posi,cnt;
void printans(string a){
    posi=0;
    while(posi<=screenwidth){
        clearsc();
        cnt=0;
        while(cnt<posi){
            cout<<" ";
            cnt++;
        }
        cout<<a;
        posi++;
    }
    while(posi>=0){
        clearsc();
        cnt=0;
        while(cnt<posi){
            cout<<" ";
            cnt++;
        }
        cout<<a;
        posi--;
    }
}
int main(){
    cin>>a;
    while(1){
        printans(a);_sleep(DURINTE);
    }
    return 0;
}