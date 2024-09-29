#include <iostream>
#include <fstream>
#include <stdio.h>
#include <list>
#include <string>
#include <stdlib.h>
using namespace std;
inline void print(){
    cout<<"Input the number to switch functions"<<endl;
    cout<<"1 . Show the warehouse list"<<endl;
    cout<<"2 . import into the warehouse"<<endl;
    cout<<"3 . export from the warehouse"<<endl;
    cout<<"4 . exit the program"<<endl;
}
list<string> s;
list<int> cnt;
string name;int num;bool flg=0;
int main(){
    ifstream cfile("warehouse.txt");
    if(!cfile.eof()){
        while(cfile>>name>>num){
            s.push_back(name);
            cnt.push_back(num);
        }
    }
    cfile.close();
    print();
    int opt;fstream ofile("warehouse.txt",ios::trunc|ios::out);
    while(cin>>opt){
        list<string>::iterator it1;
        list<int>::iterator it2;
        num=0;
        if(s.size()){
            it1=s.begin();
            it2=cnt.begin();
        }
        if(opt==1){
            if(!s.size()){
                cout<<"error : empty warehouse"<<endl;
                continue;
            }
            else for(;it1!=s.end();it1++,it2++){
                cout<<*it1<<" "<<*it2<<endl;
            }
        }
        else if(opt==2){
            cout<<"please input the product's name and amount in order"<<endl;
            cin>>name>>num;
            if(s.size()){
                flg=0;
                for(;it1!=s.end();it1++,it2++){
                    if(*it1==name){
                        *it2=*it2+num;flg=1;
                        break;
                    }
                }
            }
            if(!flg){
                s.push_back(name);cnt.push_back(num);
            }
        }
        else if(opt==3){
            if(!s.size()){
                cout<<"error : empty warehouse"<<endl;
                continue;
            }
            cout<<"please input the product's name and amount in order"<<endl;
            cin>>name>>num;flg=0;
            for(;it1!=s.end();it1++,it2++){
                if(*it1==name){
                    if(*it2<num){
                        cout<<"error : insufficient amount"<<endl;
                    }
                    else *it2=*it2-num;
                    flg=1;
                    break;
                }
            }
            if(!flg) cout<<"error : can't find the product"<<endl;
        }
        else if(opt==4){
            cin.clear();cin.sync();ofile.clear();ofile.sync();
            if(s.size()){
                for(;it1!=s.end();it1++,it2++){
                    ofile<<*it1<<" "<<*it2<<endl;
                }
                ofile.close();
            }
            break;
        }
//        system("cls");
        _sleep(50);
        cout<<endl;print();
    }
    return 0;
}