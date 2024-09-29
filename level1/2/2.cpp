#include <bits/stdc++.h>
using namespace std;
const int maxn=100000;
long long n,len;
//bool es_arr[maxn];
//inline void es(){
//    for(int i=2;i<maxn;i++){
//        if(!es_arr[i]) continue;
//        else for(int j=i+i;j<maxn;j=j+i){
//                es_arr[j]=0;
//            }
//    }
//}
bool math_isprime(long long n){
    len=sqrt(n);
    for(int i=2;i<=len;i++){
        if(n%i==0) return 0;
    }
    return 1;
}
int main(){
    cin>>n;
//    for(int i=1;i<maxn;i++){
//        es_arr[i]=1;
//    }
//    es();
    if(math_isprime(n)) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
//    for(int i=1;i<=50;i++){
//        cout<<es_arr[i]<<endl;
//    }
    return 0;
}