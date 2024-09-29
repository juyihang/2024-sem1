#include <iostream>
#include <string>
using namespace std;
string a;
int len;
// 原始手段
void incode(){
    for(int i=0;i<len;i++){
        a[i]=(char)((int)a[i]-4)%128;
    }
}
void decode(){
    for(int i=0;i<len;i++){
        a[i]=(char)((int)a[i]+4)%128;
    }
}
int main(){
    cin>>a;
    len=a.size();
    incode();
    cout<<a<<endl;
    decode();
    cout<<a<<endl;
    return 0;
}