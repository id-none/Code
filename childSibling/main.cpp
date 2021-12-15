#include<iostream>
using namespace std;
template<class ElemType>
struct childSibling                      // 节点类
{
    ElemType data;
    childSibling<ElemType> *firstChild;   // 第一个孩子节点
    childSibling<ElemType> *nextSibling;  // 下一个兄弟节点
    childSibling();                       // 构造函数
    childSibling(ElemType val, childSibling<ElemType> *fChild = NULL, childSibling<ElemType> *nSibling = NULL);  // 构造函数
};
// 孩子节点的具体实现
template<class ElemType>
childSibling<ElemType>::childSibling()
{
    firstChild = nextSibling = NULL;
}

template<class ElemType>
childSibling<ElemType>::childSibling(ElemType val, childSibling<ElemType> *fChild, childSibling<ElemType> *nSibling)
{
    data = val;
    firstChild = fChild;
    nextSibling = nSibling;
}

template<class ElemType>
class childSiblingTree    // 节点树类
{
    protected:
        childSibling<ElemType> *root;
    public:
        childSiblingTree();
        childSiblingTree(ElemType items[],int parents[], int n);    // 通过双亲表示法的树转化为孩子兄弟链表表示法
        childSibling<ElemType>* childSiblingTreeHelp(ElemType items[],int parents[],int r, int n);     // 有助于构造函数的实现（便于递归）
        childSibling<ElemType>* FirstChild(childSibling<ElemType> *cur);  // 返回cur节点的第一个孩子节点
        childSibling<ElemType>* NextSibling(childSibling<ElemType> *cur);  // 返回下一个兄弟节点
        int getHeigth(childSibling<ElemType> *r);
        int getHeigth();    // shu
        int Degree(childSibling<ElemType> *r);
        int Degree();       // 求深度
        int hight(childSibling<ElemType> *r)
        {
            int hc,hs;
            if(r==NULL)
            return 0;
            else{
                hc=hight(r->firstChild);
                hs=hight(r->nextSibling);
                if(hc+1>hs)
                    return hc+1;
                else
                    return hs;
            }
        };
};

template<class ElemType>
childSiblingTree<ElemType>::childSiblingTree()
{
    root = NULL;    
}

template<class ElemType>
childSibling<ElemType>* childSiblingTree<ElemType>::childSiblingTreeHelp(ElemType items[],int parents[], int r,int n)
{
    if(r >= 0 && r <n){
        childSibling<ElemType> *rt = new childSibling<ElemType>(items[r]);
        childSibling<ElemType> *subRoot, *cur;
        for(int i = 0;i<n;i++){
            if(parents[i] == r){
                subRoot = childSiblingTreeHelp(items,parents,i,n);
                if(rt->firstChild == NULL){
                    rt->firstChild = subRoot;
                    cur = subRoot;
                } else {
                    cur->nextSibling = subRoot;
                    cur = subRoot; 
                }
            }
        }
        return rt;
    } else{
        return NULL;
    }
}

template<class ElemType>
childSiblingTree<ElemType>::childSiblingTree(ElemType items[],int parents[], int n)
{
    root = childSiblingTreeHelp(items,parents,0,n);
}

template<class ElemType>
childSibling<ElemType>* childSiblingTree<ElemType>::FirstChild(childSibling<ElemType> *cur)
{
    if(cur == NULL){
        return NULL;
    } else {
        return cur->firstChild;
    }
}

template<class ElemType>
childSibling<ElemType>* childSiblingTree<ElemType>::NextSibling(childSibling<ElemType> *cur)
{
    if(cur == NULL){
        return NULL;
    } else {
        return cur->nextSibling;
    }
}

template<class ElemType>
int childSiblingTree<ElemType>::getHeigth(childSibling<ElemType> *r)
{
    childSibling<ElemType> *p;
    if(r == NULL){
        return 0;
    } else {
        int max=0, h;
        for(p = FirstChild(r);p!=NULL;p = NextSibling(p)){
            h = getHeigth(p);
            max = (max < h) ? h : max;
        }
        return max+1;
    }
}

template<class ElemType>
int childSiblingTree<ElemType>::getHeigth()
{
    return hight(root);
}

template<class ElemType>
int childSiblingTree<ElemType>::Degree(childSibling<ElemType> *r)
{
    if(r == NULL){
        return 0;
    } else {
        childSibling<ElemType> *p;
        int max = 0, d = 0;
        for(p = FirstChild(r);p!=NULL;p=NextSibling(p)){
            d++;
            int sub = Degree(p);
            max = (sub < max) ? max : sub;
        }
        return (d < max) ? max : d;
    }
}

template<class ElemType>
int childSiblingTree<ElemType>::Degree()
{
    return Degree(root);
}
// 测试
int main()
{
    char items[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int parents[] = {-1, 0, 0, 0, 1, 1, 3, 3};
    int n = 8;
    childSiblingTree<char> t(items, parents, n);
    cout<<"height:"<<t.getHeigth()<<endl;
    cout<<"degree:"<<t.Degree()<<endl;
    system("pause");
    return 0;
}