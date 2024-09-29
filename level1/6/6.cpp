#include <iostream>
using namespace std;
inline void hanoi(int num,char a,char b,char c){
    if(num==1) cout<<a<<" -> "<<c<<endl;
    else{
        hanoi(num-1,a,c,b);
        cout<<a<<" -> "<<c<<endl;
        hanoi(num-1,b,a,c);
    }
}
int main(){
    hanoi(64,'A','B','C');
    return 0;
}