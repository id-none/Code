#ifndef BTREE_H
#define BTREE_H

#include <bits/stdc++.h>
using namespace std;

#define KeyType int
#define Record string
const int m = 3;

typedef struct BTNode{
    int keynum;
    struct BTNode *parent;
    KeyType key[m+1];
    struct BTNode *ptr[m+1];
    Record* recptr[m+1]‘
    BTNode()
    {
        keynum = 0;
        parent = NULL;
        for(int i = 0;i < m+1; ++i)
            ptr[i] = NULL;
    }
}BTNode,*BTree;

BTree T = NULL;

typedef struct{
    BTree pt;
    int i;
    int tag;
}result;

int Search(BTree p,int k)
{
    int i = 1;
    while(i <= p->keynum && k > p->key[i]) i++;
    return i;
}

void Search_BTree(BTree t, int k, result& r

)
{
    int i = 0;
    int found = 0;
    BTree p = t,q = NULL;
    while (p != NULL && found == 0)
    {
        i = Search(p , k);
        if(i <= p->keynum && p ->key[i] == k)
            found = 1;
        else
        {
            q = p;
            p = p->ptr[i-1];
        }
    }
    if(found == 1){
        r.i = i;
        r.pt = p;
        r.tag = 1;
    }
    else{
        r.i = i;
        r.pt = q;
        r.tag = 0;
    }
}