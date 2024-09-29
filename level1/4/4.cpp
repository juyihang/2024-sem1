#include <iostream>
using namespace std;
const int maxn=120;
bool number[maxn];
int prime[]={1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
inline void fill(int sum,int cnt){
    if(cnt>3) return;
    if(sum>100) return;
    if(number[sum]) return;
    number[sum]=1;
    for(int i=1;i<=25;i++){
        fill(sum+prime[i],cnt+1);
    }
}
int main(){
    for(int i=0;i<=100;i++)number[i]=0;
    fill(0,0);
    for(int i=5;i<=100;i++){
        if(number[i]) cout<<i<<" yes"<<endl;
        else cout<<i<<" no"<<endl;
    }
    return 0;
}