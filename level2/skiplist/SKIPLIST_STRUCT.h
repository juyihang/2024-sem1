#pragma once

const int MAX_LEVEL=7;
inline int S_min(int a,int b);
inline int GetLevel();
struct SkipList_Node{
    int Level;
    int data;
    int cnt;
    SkipList_Node* next_list;
};
SkipList_Node* update[MAX_LEVEL+5];
SkipList_Node *head,*tail;
inline void init();
SkipList_Node *SkipList_FindPosition(int data);
SkipList_Node *SkipList_BuildNode(int data);
bool SkipList_EraseNode(int data);