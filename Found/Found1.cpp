//���� ˳��� BTS����������
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct{
    int key;    // �ؼ�����
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

//˳�����ҷ�
int Search(int a[], int n, int k)
{
    for(int i = 0;i < n; ++i)
    {
        if(a[i] == k) return i;
    }
    return 0;
}

//������۰����(?����Ƕ���)(�ǵݹ�)
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
//������۰����(?����Ƕ���)(�ݹ�)
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

//�ֿ����(����˳�����)
//int FSearch(int R1[], int R2[],int low, int high, int k)

//����������BST
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

//��������Ľ����
int NodeNum(BTNode * root)
{
    if(root== NULL) // �ݹ����
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
        if(key == bt->key)   //�ؼ����Ѿ������޷�����
            return 0;
        else if(key > bt->key)
            return BSTInsert2(bt->lchild, key);
        else 
            return BSTInsert2(bt->rchild, key);
    }
}
//��������������ؼ���
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
        if(key == bt->key)   //�ؼ����Ѿ������޷�����
            return 0;
        else if(key < bt->key)
            return BSTInsert(bt->lchild, key);
        else 
            return BSTInsert(bt->rchild, key);
    }
}

//�����������Ĺ���
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
//ɾ�����
void Delete(BTNode* &p){
    BTNode  *q, *s;
    if (p->rchild == NULL) {  // �������� ��ֻ��Ҫ�ؽ�����������
        p = p->lchild; 
    }else if (p->lchild == NULL){  // �������� ��ֻ��Ҫ�ؽ�����������
        p = p->rchild;  
    }
    else{  // ��������������
        q = p;
        s = p->lchild;
        
        while (s->rchild) {  // ���ҵ���ͷ���ҵ���ɾ����ǰ��  
            q = s;
            s = s->rchild;
        }
        p->key = s->key;  // s ָ��ɾ������ֱ��ǰ�� ������ɾ���ǰ����ֵȡ����ɾ����ֵ��
        if (q != p)
            q->rchild = s->lchild;  // �ؽ� q ��������
        else
            q->lchild = s->lchild;  // �ؽ� q ��������
        free(s);
    }
}

//ɾ���ؼ���
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

//ƽ�������AVL��lsize��
int return_lsize(BTNode * &T)
{
     int size = NodeNum(T->lchild) + 1;
     T->lsize=size;
     return T->lsize;
}

//�������������
void InOrderTraverse(BTNode* T)
{
    if(!T)
        return;
    return_lsize(T);
    InOrderTraverse(T->lchild);
    printf("%d ",T->key);
    InOrderTraverse(T->rchild);
}

//�ж϶������Ƿ�Ϊ����������������
int Judge(BTNode* root,int &MAX){
    if(root == NULL){//��Ϊ����Ϊ���������� 
        return 1;
    }
    int bst_l,bst_r;
    bst_l = Judge(root->lchild,MAX);//�ж��������Ƿ�Ϊ����������
    if(!bst_l || MAX >= root->key){
        return 0;
    }
    MAX = root->key;
    bst_r = Judge(root->rchild,MAX);//�ж��������Ƿ�Ϊ����������
    return bst_r;
}
//��������������йؼ��ֲ�С��x������Ԫ�أ�Ҫ��ʱ�临�Ӷ�ΪO(log n + m)(�ݹ�)��8��
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

//��������������йؼ��ֲ�С��x������Ԫ�أ�Ҫ��ʱ�临�Ӷ�ΪO(log n + m)(�ǵݹ�)
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
//lsize ����
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
//lsieze����
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

//һ��������Ĵ���
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
        printf("�����");
    else
        printf("�Ǽٵ�");
    system("pause");
}
// 1 2 3 4 5 6 7 8 9 10