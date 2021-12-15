#include<iostream>
using namespace std;
#define max 50
template<class Elemtype>
class SqList
{   
private:
    int length;
    int maxsize;
    Elemtype data[max];
public:
    SqList(){length=0;};
    SqList(Elemtype a[],int n){
        length=n;
        for (int i = 0; i < n; i++)
            data[i]=a[i];
    };
    void initSqlist(SqList<Elemtype> &a){
        a.length=0;
        cout<<"初始化完成，初始单链表长度为"<<a.length<<endl;;
    };
    int Length()
    {
        return length;    };
};
int main()
{
    SqList<int> a;
    cout<<a.Length()<<endl;
    system("pause");
    
}