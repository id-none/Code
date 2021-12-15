//查找 顺序表 BTS二叉排序树
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct{
    int key;    // 关键字域
}Elemtype;

typedef struct 
{
    int key;
    int low,high;
}indexElem;
//indexElem index[100];

struct BTNode{
    int key;
    int count;
    int lsize;
    struct BTNode *lchild;
    struct BTNode *rchild;
};

//顺序表查找法
int Search(int a[], int n, int k)
{
    for(int i = 0;i < n; ++i)
    {
        if(a[i] == k) return i;
    }
    return 0;
}

//有序表折半查找(?这就是二分)(非递归)
int BSearch1(int R[],int low, int high, int k)
{
    int mid;
    while(low <= high)
    {
        mid = (low + high)/2;
        if(R[mid] == k) 
            return mid;
        else if(R[mid] > k)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;
}
//有序表折半查找(?这就是二分)(递归)
int BSearch2(int R[],int low, int high, int k)
{
    int mid;
    if(low > high)
        return 0;
    else
    {
        if(R[mid] > k)
            mid = BSearch2(R, low, mid - 1, k);
        else
            mid = BSearch2(R, mid + 1, high, k);
    }
    return mid;
}

//分块查找(索引顺序查找)
//int FSearch(int R1[], int R2[],int low, int high, int k)

//二叉排序树BST
BTNode* BSTSearch(BTNode* bt, int key)
{
    if(bt == NULL)
        return NULL;
    else
    {
        if(bt->key == key)
        {
            bt->count ++;
            return bt;
        }
        else if(key < bt->key)
            return BSTSearch(bt->lchild,key);
        else
            return BSTSearch(bt->rchild,key);
    }
}

//求二叉树的结点数
int NodeNum(BTNode * root)
{
    if(root== NULL) // 递归出口
        return 0;
    return NodeNum(root->lchild) + NodeNum(root->rchild) + 1;
}

int BSTInsert2(BTNode* &bt,int key)
{
    if(bt == NULL)
    {
        bt = (BTNode*)malloc(sizeof(BTNode));
        bt->lchild = bt->rchild = NULL;
        bt->key = key;
        return 1;
    }
    else
    {
        if(key == bt->key)   //关键字已经存在无法插入
            return 0;
        else if(key > bt->key)
            return BSTInsert2(bt->lchild, key);
        else 
            return BSTInsert2(bt->rchild, key);
    }
}
//二叉排序树插入关键字
int BSTInsert(BTNode* &bt, int key)
{
    if(bt == NULL)
    {
        bt = (BTNode*)malloc(sizeof(BTNode));
        bt->lchild = bt->rchild = NULL;
        bt->key = key;
        bt->count = 0;
        return 1;
    }
    else
    {
        if(key == bt->key)   //关键字已经存在无法插入
            return 0;
        else if(key < bt->key)
            return BSTInsert(bt->lchild, key);
        else 
            return BSTInsert(bt->rchild, key);
    }
}

//二叉排序树的构造
void CreatBST(BTNode* &bt, int key[], int n)
{
    bt = NULL;
    for (int i = 0; i < n; i++)
    {
        /* code */
        BSTInsert(bt,key[i]);
    }
}
void Creat(BTNode *& bt, int key[],int n)
{
    bt = NULL;
    for (int i = 0; i < n; i++)
    {
        /* code */
        BSTInsert2(bt,key[i]);
    }
}
//删除结点
void Delete(BTNode* &p){
    BTNode  *q, *s;
    if (p->rchild == NULL) {  // 右子树空 则只需要重接它的左子树
        p = p->lchild; 
    }else if (p->lchild == NULL){  // 左子树空 则只需要重接它的右子树
        p = p->rchild;  
    }
    else{  // 左右子树都不空
        q = p;
        s = p->lchild;
        
        while (s->rchild) {  // 向右到尽头，找到待删结点的前驱  
            q = s;
            s = s->rchild;
        }
        p->key = s->key;  // s 指向被删除结点的直接前驱 （将被删结点前驱的值取代被删结点的值）
        if (q != p)
            q->rchild = s->lchild;  // 重接 q 的右子树
        else
            q->lchild = s->lchild;  // 重接 q 的左子树
        free(s);
    }
}

//删除关键字
void DeleteBST(BTNode* &bt, int key)
{
    if(!bt)
        return;
    else{
        if(key == bt->key)
            Delete(bt);
        else if(key < bt->key)
            DeleteBST(bt->lchild,key);
        else if(key > bt->key)
            DeleteBST(bt->rchild,key);
    }
}

//平衡二叉树AVL树lsize域
int return_lsize(BTNode * &T)
{
     int size = NodeNum(T->lchild) + 1;
     T->lsize=size;
     return T->lsize;
}

//中序遍历二叉树
void InOrderTraverse(BTNode* T)
{
    if(!T)
        return;
    return_lsize(T);
    InOrderTraverse(T->lchild);
    printf("%d ",T->key);
    InOrderTraverse(T->rchild);
}

//判断二叉树是否为二叉排序树第七题
int Judge(BTNode* root,int &MAX){
    if(root == NULL){//树为空则为二叉排序树 
        return 1;
    }
    int bst_l,bst_r;
    bst_l = Judge(root->lchild,MAX);//判断左子树是否为二叉排序树
    if(!bst_l || MAX >= root->key){
        return 0;
    }
    MAX = root->key;
    bst_r = Judge(root->rchild,MAX);//判断右子树是否为二叉排序树
    return bst_r;
}
//输出二叉排序树中关键字不小于x的数据元素，要求时间复杂度为O(log n + m)(递归)第8题
void More_x(BTNode* T,int x)
{
    /*if(!T)
        return;
    More_x(T->rchild,x);
    if(T->key >= x)
        printf("%d ",T->key);
    More_x(T->lchild,x);*/
    /*if(T->key > x)
        More_x(T->lchild,x);
    if(T->key == x)
    {
        printf("%d ",T->key);
        More_x(T->lchild,x);
    }
    else 
    {
        More_x(T->rchild,x);
        printf("%d ",T->key);
        More_x(T->lchild,x);
    }*/
    if(T)
    {
        More_x(T->rchild,x);
        if(T->key < x)
            return;
        cout << T->key << " ";
        More_x(T->lchild,x);

    }
}

//输出二叉排序树中关键字不小于x的数据元素，要求时间复杂度为O(log n + m)(非递归)
void More_x2(BTNode *T, int x)
{
    if(!T)
        return;
    stack<BTNode *> s;
    BTNode* cur = T;
    while(!s.empty() || cur)
    {
        while(cur){
            s.push(cur);
            cur = cur ->lchild;
        }
        BTNode* node = s.top();
        s.pop();
        if(node->key >= x)
            printf("%d ",node->key);
        cur = node->rchild;
    }
}
//lsize 排序
int Sort(BTNode * T,int k)
{
    if(!T)
        return 0;
    int a[20];
    int i = 0;
    stack<BTNode *> s;
    BTNode* cur = T;
    while(!s.empty() || cur)
    {
        while(cur){
            s.push(cur);
            cur = cur ->lchild;
        }
        BTNode* node = s.top();
        s.pop();
        a[i] = node->lsize;
        cur = node->rchild;
        i++ ;
    }
    sort(a,a+NodeNum(T)+1);
    return a[k];
}
//lsieze排序
BTNode* locale_AVL(BTNode* t,int k)
{
    if(!t)
        return NULL;
    if(t->lsize == k)
        return t;
    else
        if(t->lsize > k)
            return locale_AVL(t->lchild,k);
        else
            return locale_AVL(t->rchild,k);
}

//一般二叉树的创建
/*BTNode* Creat2(int pre[], int in[], int n)
{
    BTNode *r;
    Creat2(r, pre, in, 0, n - 1, 0, n - 1);
    BTNode * bt = new (BTNode*)(r);
    return bt;
}
*/
int main()
{
    BTNode *A;
    int a[10] = {0,2,3,5,4,6,8,7,10,9};
    int n = -1;
    CreatBST(A,a,10);
    DeleteBST(A,5);
    if(!BSTSearch(A,1))
        BSTInsert(A,1);
    InOrderTraverse(A);

    printf("\n");
    //cout << return_lsize(A);
    More_x(A,5);
    //More_x2(A,5);
    if(Judge(A,n) == 1)
        printf("是真的");
    else
        printf("是假的");
    system("pause");
}
// 1 2 3 4 5 6 7 8 9 10