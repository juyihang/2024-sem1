#include <iostream>
#include <string.h>
//array function
using namespace std;
const int MAXN=100000;
int num,val;

struct Link_Node{
    int value;
    int next;//prev
}node[MAXN];
int head,tail,tot;bool rev=0;

inline void init(){
    tot=2,head=1,tail=2;
    node[head].next=tail;
//    node[tail].prev=head;
}
int insert(int p,int v){
    int q=++tot;
    node[q].value=v;

//    node[node[p].next].prev=q;
    node[q].next=node[p].next;

    node[p].next=q;
//    node[q].prev=p;

    return 1;
}
int erase(int p){
//    node[node[p].prev].next=node[p].next;
//    node[node[p].next].prev=node[p].prev;
    return 1;
}
inline void clear(){
    memset(node,0,sizeof(node));
    head=tail=tot=0;
}
int reverse(int p,int fa){
    if(p==2&&!rev){
        node[p].next=fa;rev=1;return 1;
    }
    if(p==1&&rev){
        node[p].next=fa;rev=0;return 1;
    }
    reverse(node[p].next,p);
    node[p].next=fa;
    return 1;
}
int findk(int k,int v){
    int tmp,p,cnt;cnt=0;
    if(!rev) p=head;
    else p=tail;
    tmp=3-p;
    p=node[p].next;
    while(p!=tmp){
        if(node[p].value==v) k--;
        cnt++;
        if(k<=0) return cnt;
        p=node[p].next;
    }
    return -1;
}
int main(){
    init();
    cin>>num;//图省事而这样写
    cin>>val;
    insert(head,val);
    for(int i=2;i<=num;i++){
        cin>>val;
        insert(tot,val);
    }
    int seq=node[head].next;
    while(seq!=tail){
        cout<<node[seq].value<<" ";
        seq=node[seq].next;
    }
    cout<<endl;
    reverse(head,0);
    seq=node[tail].next;
    while(seq!=head){
        cout<<node[seq].value<<" ";
        seq=node[seq].next;
    }
    cout<<endl;
    cout<<findk(1,5)<<endl;
    cout<<findk(2,5)<<endl;
    return 0;
}