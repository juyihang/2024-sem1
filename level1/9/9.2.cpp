#include <iostream>
//pointer function
using namespace std;
struct List_Node{
    int value;
    List_Node *next,*prev;
};
int num,val;bool rev=0;
List_Node *head,*tail;
inline void init(){
    head=new List_Node();
    tail=new List_Node();
    head->next=tail;
//    tail->prev=head;
}
void insert(List_Node *p,int v){
    List_Node *q=new List_Node();
    q->value=v;
//    p->next->prev=q;
    q->next=p->next;
    p->next=q;
//    q->prev=p;
}
void erase(List_Node *p){
    p->next->prev=p->prev;
    p->prev->next=p->next;
    delete p;
}
void clear(){
    while(head!=tail){
        head=head->next;
        delete head->prev;
    }
    delete tail;
}
void reverse(List_Node *p,List_Node *fa){
    if(p==tail&&!rev){
        p->next=fa;rev=1;return;
    }
    if(p==head&&rev){
        p->next=fa;rev=0;return;
    }
    reverse(p->next,p);
    p->next=fa;
}
int findk(int k,int v){
    List_Node *p,*tmp;int cnt=0;
    if(!rev) p=head,tmp=tail;
    else p=tail,tmp=head;
    p=p->next;
    while(p!=tmp){
        if(p->value==v) k--;
        cnt++;
        if(k<=0) return cnt;
        p=p->next;
    }
    return -1;
}
int main(){
    init();
    cin>>num;List_Node *s=head;
    while(num--){
        cin>>val;
        insert(s,val);
        s=s->next;
    }
    s=head->next;
    while(s!=tail){
        cout<<s->value<<" ";
        s=s->next;
    }
    cout<<endl;
    reverse(head,NULL);
    s=tail->next;
    while(s!=head){
        cout<<s->value<<" ";
        s=s->next;
    }
    cout<<endl;
    cout<<findk(1,5)<<endl;
    cout<<findk(2,5)<<endl;
    return 0;
}