#ifndef AVL_H
#define AVL_H

#include <bits/stdc++.h>
using namespace std;

class node{
public:
    int data,h,lsize,size;
    node *ls,*rs;
    node(){}
    node(int nelem,node* l=nullptr,node* r=nullptr):data(nelem),size(1),lsize(1),h(1),ls(nullptr),rs(nullptr){}
};

class AVL{
public:
    AVL():root(nullptr){}
    AVL(vector<int> &v);
    void traverse();
    void insert(int elem);
    bool find(int elem);
    void del(int elem);
    void findelems(int elem);
    int kth(int x);
private:
    int __kth(int x,node* rt);
    void __findelems(int elem,node* rt);
    node* __del(int elem,node* rt);
    node* __insert(int elem,node* rt);
    bool __find(int elem,node* rt);
    int get_balance(node* rt) {return rt==nullptr?0:get_h(rt->ls)-get_h(rt->rs);}
    int get_h(node *rt) {return rt==nullptr?0:rt->h;}
    int get_lsize(node *rt) {return rt==nullptr?0:rt->lsize;};
    int get_size(node *rt) {return rt==nullptr?0:rt->size;};
    void pushup(node *rt);
    void __traverse(node* now);
    node* ll_rotate(node *rt);
    node* rr_rotate(node *rt);
    node* lr_rotate(node *rt);
    node* rl_rotate(node *rt);
    node* root;
};

int AVL::kth(int x){
    if(root==nullptr) {
        cout<<"empty tree!"<<endl;
        return -1;
    }
    if(x<0||x>root->size){
        cout<<"illegal input"<<endl;
        return -1;
    }
    return __kth(x,root);
}

int AVL::__kth(int x,node* rt){
    if(rt->lsize==x) return rt->data;
    else if(rt->lsize>x) return __kth(x,rt->ls);
    else return __kth(x-rt->lsize,rt->rs);
}

void AVL::pushup(node *rt){
    rt->h = max(get_h(rt->ls),get_h(rt->rs))+1;
    rt->size = get_size(rt->ls)+get_size(rt->rs)+1;
    rt->lsize = get_size(rt->ls)+1;
}

void AVL::findelems(int elem){
    if(root==nullptr) {
        cout<<"empty tree!"<<endl;
        return ;
    }
    __findelems(elem,root);
}

void AVL::__findelems(int elem,node* rt){
    if(rt==nullptr) return ;
    if(rt->data>elem){
        __findelems(elem,rt->ls);
        cout<<rt->data<<" ";
        __findelems(elem,rt->rs);
    }
    if(rt->data<=elem){
        __findelems(elem,rt->rs);
    }
}

AVL::AVL(vector<int> &v){
    root=nullptr;
    for(vector<int>::iterator it=v.begin();it!=v.end();it++)
        insert(*it);
}

void AVL::del(int elem){
    if(root==nullptr) return ;
    root = __del(elem,root);
}

node* AVL::__del(int elem,node* rt){
    if(rt==nullptr) return nullptr;
    if(rt->data>elem) rt->ls = __del(elem,rt->ls);
    else if(rt->data<elem) rt->rs = __del(elem,rt->rs);
    else {
        if(rt->ls!=nullptr){
            node* p=rt->ls;
            while(p->rs)
                p = p->rs;
            rt->data = p->data;
            rt->ls = __del(rt->data,rt->ls);
        }else if(rt->ls==nullptr && rt->rs!=nullptr){
            node* p=rt->rs;
            while(p->ls)
                p = p->ls;
            rt->data = p->data;
            rt->rs = __del(rt->data,rt->rs);
        }else{
            delete rt;
            return nullptr;
        }
    }
    pushup(rt);
    int delta = get_balance(rt);
    int delta_ls = get_balance(rt->ls);
    int delta_rs = get_balance(rt->rs);
    if(delta>1 && delta_ls>0)
        return ll_rotate(rt);
    if(delta>1 && delta_ls<0)
        return lr_rotate(rt);
    if(delta<-1 && delta_rs>0)
        return rl_rotate(rt);
    if(delta<-1 && delta_rs<0)
        return rr_rotate(rt);
    return rt;
}

bool AVL::find(int elem){
    if(root==nullptr) return false;
    return __find(elem,root);
}

bool AVL::__find(int elem,node* rt){
    if(rt==nullptr) return false;
    if(rt->data==elem) return true;
    if(rt->data>elem) return __find(elem,rt->ls);
    if(rt->data<elem) return __find(elem,rt->rs);
    return false;
}

void AVL::insert(int elem){
    if(root==nullptr){
        root = new node(elem);
        return ;
    }
    root = __insert(elem,root);
}

node* AVL::__insert(int elem,node* rt){
    if(rt==nullptr)
        return new node(elem);
    if(rt->data>elem) 
        rt->ls = __insert(elem,rt->ls);
    else if(rt->data<elem) 
        rt->rs = __insert(elem,rt->rs);
    else 
        return new node(elem);
    pushup(rt);
    int delta = get_balance(rt);
    int delta_ls = get_balance(rt->ls);
    int delta_rs = get_balance(rt->rs);
    if(delta>1 && delta_ls>0)
        return ll_rotate(rt);
    if(delta>1 && delta_rs<0)
        return lr_rotate(rt);
    if(delta<-1 && delta_rs>0)
        return rl_rotate(rt);
    if(delta<-1 && delta_rs<0)
        return rr_rotate(rt);
    return rt;
}

node* AVL::lr_rotate(node *rt){
    rt->ls = rr_rotate(rt->ls);
    return ll_rotate(rt->rs);
}

node* AVL::rl_rotate(node *rt){
    rt->rs = ll_rotate(rt->rs);
    return rr_rotate(rt);
}

node* AVL::rr_rotate(node *rt){
    node *tmp = rt->rs;
    rt->rs = tmp->ls;
    tmp->ls = rt;
    pushup(rt);
    pushup(tmp);
    return tmp;
}

node* AVL::ll_rotate(node *rt){
    node *tmp = rt->ls;
    rt->ls = tmp->rs;
    tmp->rs = rt;
    pushup(rt);
    pushup(tmp);
    return tmp;
}

void AVL::traverse(){
    if(root==nullptr){
        cout<<"empty tree!"<<endl;
        return ;
    }
    __traverse(root);
    cout<<endl;
}

void AVL::__traverse(node *now){
    if(now->ls!=nullptr) __traverse(now->ls);
    cout<<now->data<<" ";
    if(now->rs!=nullptr) __traverse(now->rs);
}

#endif 
/* AVL_H */