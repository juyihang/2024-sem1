
#include <cstdlib>
#include <ctime>

#define SKPLST_LV_INIT; ctime(0);

const int MAX_LEVEL=7;

inline int S_min(int a,int b){
    return a>b?:a,b;
}

inline int GetLevel(){
    int Level=1;
    while(rand()%2) Level++;
    return S_min(Level,MAX_LEVEL);
}

struct SkipList_Node{
    int Level;
    int data;
    //int cnt;
    SkipList_Node** next_list;
};
int SkipList_Node_Count=0;
SkipList_Node* update[MAX_LEVEL+5];
SkipList_Node *head,*tail;
inline void init(){
    head->Level=MAX_LEVEL;
    tail->Level=MAX_LEVEL;
    head->next_list=(SkipList_Node **) malloc(sizeof(SkipList_Node)*(MAX_LEVEL));
    tail->next_list=(SkipList_Node **) malloc(sizeof(SkipList_Node)*(MAX_LEVEL));
    for(int i=0;i<MAX_LEVEL;i++){
        head->next_list[i]=tail;
    }
}

//p=head
SkipList_Node* SkipList_FindPosition(int data){
    SkipList_Node *p=head;
    for(int i=MAX_LEVEL-1;i>=0;i--){
        while((p->next_list[i])->data<data&&p->next_list[i]!=tail){
            p=p->next_list[i];
        }
    }
    p=p->next_list[0];
    if(p->data==data) return p;
    else return NULL;
}

SkipList_Node* SkipList_BuildNode(int data){
    SkipList_Node *p=head;
    for(int i=MAX_LEVEL-1;i>=0;i--){
        while((p->next_list[i])->data<data&&p->next_list[i]!=tail){
            p=p->next_list[i];
        }
        update[i]=p;
    }
    if(p->next_list[0]->data==data) return NULL;
    int New_Level=GetLevel();
    SkipList_Node *q=(SkipList_Node *) malloc(sizeof(SkipList_Node)*(New_Level));
    for(int i=0;i<New_Level;i++){
        q->next_list[i]=(update[i]->next_list[i]);
        update[i]->next_list[i]=q;
    }
    SkipList_Node_Count++;
    return q;
}

bool SkipList_EraseNode(int data){
    SkipList_Node *p=head;
    for(int i=MAX_LEVEL-1;i>=0;i--){
        while((p->next_list[i])->data<data&&p->next_list[i]!=tail){
            p=p->next_list[i];
        }
        update[i]=p;
    }
    p=p->next_list[0];
    if(p->data!=data) return 0;
    for(int i=0;i<p->Level;i++){
        update[i]->next_list[i]=p->next_list[i];
    }
    delete p;
    SkipList_Node_Count--;
    return 1;
}
